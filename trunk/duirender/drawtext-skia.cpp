#include "drawtext-skia.h"

#define DT_ELLIPSIS (DT_PATH_ELLIPSIS|DT_END_ELLIPSIS|DT_WORD_ELLIPSIS)
#define CH_ELLIPSIS L"..."
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))

static size_t breakTextEx(const SkPaint *pPaint, const wchar_t* textD, size_t length, SkScalar maxWidth,
                          SkScalar* measuredWidth) 
{
    size_t nLineLen=pPaint->breakText(textD,length*sizeof(wchar_t),maxWidth,measuredWidth,SkPaint::kForward_TextBufferDirection);
    if(nLineLen==0) return 0;
    nLineLen/=sizeof(wchar_t);

    const wchar_t * p=textD;
    for(size_t i=0;i<nLineLen;i++, p++)
    {
        if(*p == L'\r')
        {
            if(i<nLineLen-1 && p[1]==L'\n') return i+2;
            else return i;
        }else if(*p == L'\n')
        {
            return i+1;
        }
    }
    return nLineLen;
}

SkRect DrawText_Skia(SkCanvas* canvas,const wchar_t *text,int len,SkRect box,const SkPaint& paint,UINT uFormat)
{
	if(len<0)	len = wcslen(text);
    SkTextLayoutEx layout;
    layout.init(text,len,box,paint,uFormat);
    
    return layout.draw(canvas);
}

//////////////////////////////////////////////////////////////////////////
void SkTextLayoutEx::init( const wchar_t text[], size_t length,SkRect rc, const SkPaint &paint,UINT uFormat )
{
    if(uFormat & DT_NOPREFIX)
    {
        m_text.setCount(length);
        memcpy(m_text.begin(),text,length*sizeof(wchar_t));
    }else
    {
        m_prefix.reset();
        SkTDArray<wchar_t> tmp;
        tmp.setCount(length);
        memcpy(tmp.begin(),text,length*sizeof(wchar_t));
        for(int i=0;i<tmp.count();i++)
        {
            if(tmp[i]==L'&')
            {
                tmp.remove(i,1);
                if(i<tmp.count()-1) m_prefix.push(i);
                if(i<tmp.count()-1 && tmp[i+1]==L'&') i++;  //skip the next "&"
            }
        }
        m_text=tmp;
    }

    m_paint=&paint;
    m_rcBound=rc;
    m_uFormat=uFormat;
    buildLines();
}

void SkTextLayoutEx::buildLines()
{
    m_lines.reset();

    if(m_uFormat & DT_SINGLELINE)
    {
        m_lines.push(0);
    }else
    {
        const wchar_t *text = m_text.begin();
        const wchar_t* stop = m_text.begin() + m_text.count();

        int lineHead=0;
        while(lineHead<m_text.count())
        {
            m_lines.push(lineHead);
            size_t line_len = breakTextEx(m_paint,text, stop - text, m_rcBound.width(),0);
            text += line_len;
            lineHead += line_len;
        };
    }
}

SkScalar SkTextLayoutEx::drawLine( SkCanvas *canvas, SkScalar x, SkScalar y, int iBegin,int iEnd,SkScalar fontHei )
{
    const wchar_t *text=m_text.begin()+iBegin;

    if(!(m_uFormat & DT_CALCRECT))
    {
        canvas->drawText(text,(iEnd-iBegin)*sizeof(wchar_t),x,y,*m_paint);
        int i=0;
        while(i<m_prefix.count())
        {
            if(m_prefix[i]>=iBegin)
                break;
            i++;
        }
        while(i<m_prefix.count() && m_prefix[i]<iEnd)
        {
            SkScalar x1 = x + m_paint->measureText(text,(m_prefix[i]-iBegin)*sizeof(wchar_t));
            SkScalar x2 = x + m_paint->measureText(text,(m_prefix[i]-iBegin+1)*sizeof(wchar_t));
            canvas->drawLine(x1,y+1,x2,y+1,*m_paint); //�����»���
            i++;
        }
    }
    return m_paint->measureText(text,(iEnd-iBegin)*sizeof(wchar_t));
}

SkScalar SkTextLayoutEx::drawLineWithEndEllipsis( SkCanvas *canvas, SkScalar x, SkScalar y, int iBegin,int iEnd,SkScalar fontHei,SkScalar maxWidth )
{
    SkScalar widReq=m_paint->measureText(m_text.begin()+iBegin,(iEnd-iBegin)*sizeof(wchar_t));
    if(widReq<m_rcBound.width())
    {
        return drawLine(canvas,x,y,0,m_text.count(),fontHei);
    }else
    {
        SkScalar fEllipsisWid=m_paint->measureText(CH_ELLIPSIS,sizeof(CH_ELLIPSIS)-sizeof(wchar_t));

        SkScalar fWid=fEllipsisWid;
        int i=0;
        const wchar_t *text=m_text.begin()+iBegin;
        while(i<(iEnd-iBegin))
        {
            fWid += m_paint->measureText(text+i,sizeof(wchar_t));
            if(fWid > maxWidth) break;
            i++;
        }
        drawLine(canvas,x,y,0,i,fontHei);
        if(!(m_uFormat & DT_CALCRECT)) canvas->drawText(CH_ELLIPSIS,sizeof(CH_ELLIPSIS)-sizeof(wchar_t),x+fWid-fEllipsisWid,y,*m_paint);
        return fWid;
    }
}

SkRect SkTextLayoutEx::draw( SkCanvas* canvas )
{
    float  fontHeight,textHeight;
    SkPaint::FontMetrics metrics;

    m_paint->getFontMetrics(&metrics);
    fontHeight = metrics.fDescent-metrics.fAscent;
    textHeight = fontHeight;

    float lineSpan = metrics.fBottom-metrics.fTop;

    SkRect rcDraw = m_rcBound;

    float  x;
    switch (m_paint->getTextAlign()) 
    {
    case SkPaint::kCenter_Align:
        x = SkScalarHalf(m_rcBound.width());
        break;
    case SkPaint::kRight_Align:
        x = m_rcBound.width();
        break;
    default://SkPaint::kLeft_Align:
        x = 0;
        break;
    }
    x += m_rcBound.fLeft;

    canvas->save();

    canvas->clipRect(m_rcBound);

    float height = m_rcBound.height();
    float y=m_rcBound.fTop - metrics.fAscent;
    if(m_uFormat & DT_SINGLELINE)
    {//������ʾ
        rcDraw.fBottom = rcDraw.fTop + lineSpan;
        if(m_uFormat & DT_VCENTER) 
        {
            y += (height - textHeight)/2.0f;
        }
        if(m_uFormat & DT_ELLIPSIS)
        {//ֻ֧������β����ʡ�Ժ�
            rcDraw.fRight = rcDraw.fLeft + drawLineWithEndEllipsis(canvas,x,y,0,m_text.count(),fontHeight,m_rcBound.width());
        }else
        {
            rcDraw.fRight = rcDraw.fLeft + drawLine(canvas,x,y,0,m_text.count(),fontHeight);
        }
    }else
    {//������ʾ
        SkScalar maxLineWid=0;
        int iLine = 0;
        while(iLine<m_lines.count())
        {
            if(y + lineSpan + metrics.fAscent >= m_rcBound.fBottom) 
                break;  //the last visible line
            int iBegin=m_lines[iLine];
            int iEnd = iLine<(m_lines.count()-1)?m_lines[iLine+1]:m_text.count();
            SkScalar lineWid = drawLine(canvas,x,y,iBegin,iEnd,fontHeight);
            maxLineWid = MAX(maxLineWid,lineWid);
            y += lineSpan;
            iLine ++;
        }
        if(iLine<m_lines.count())
        {//draw the last visible line
            int iBegin=m_lines[iLine];
            int iEnd = iLine<(m_lines.count()-1)?m_lines[iLine+1]:m_text.count();
            SkScalar lineWid;
            if(m_uFormat & DT_ELLIPSIS)
            {//ֻ֧������β����ʡ�Ժ�
                lineWid=drawLineWithEndEllipsis(canvas,x,y,iBegin,iEnd,fontHeight,m_rcBound.width());
            }else
            {
                lineWid=drawLine(canvas,x,y,iBegin,iEnd,fontHeight);
            }
            maxLineWid = MAX(maxLineWid,lineWid);
            y += lineSpan;
        }
        rcDraw.fRight = rcDraw.fLeft + maxLineWid;
        rcDraw.fBottom = rcDraw.fTop + y;
    }
    canvas->restore();
    return rcDraw;
}
