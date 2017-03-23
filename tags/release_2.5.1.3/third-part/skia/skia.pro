######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 25 09:55:47 2014
######################################################################

#--------------------------------------------------------------------------------------------------------------------------
#   重要修改：
#	Skia支持SSE3优化，skia自动检测CPU指令集，不支持SSE3时自动使用SSE2,SSE2是最低要求。
#	修改了src\opts\SkBitmapProcState_opts_SSSE3.cpp的源代码，原有代码需要定义SK_CPU_SSE_LEVEL >= SK_CPU_SSE_LEVEL_SSSE3(31)
#   才生成SSE3的处理代码，同时定义了这个宏又将导致SkBitmapProcState::platformProcs在没有检测CPU支持的情况下自动选择SSE3处理。
#   导致在不支持SSE3的CPU上运行崩溃。
#                                                 启程软件 2016年11月4日
#----------------------------------------------------------------------------------------------------------------------------


TEMPLATE = lib
TARGET = skia
CONFIG += staticlib

INCLUDEPATH += . \
		include/config \
		include/core \
		src/core \
		include/gpu \
		src/gpu \
		include/images \
		include/utils \
		include/utils/win \
		src/utils \
		include/ports \
		include/text \
		include/effects \
		src/sfnt \
		include/pathops \
		src/image \
		src/opts \
		src/lazy \

dir = ../..
include($$dir/common.pri)

DEFINES += SK_IGNORE_ETC1_SUPPORT 

win32-msvc*{
    QMAKE_CXXFLAGS += /wd4244 /wd4800 /wd4100
}

# Input
SOURCES += src\fonts\SkFontMgr_indirect.cpp
SOURCES += src\fonts\SkGScalerContext.cpp
HEADERS += src\fonts\SkGScalerContext.h
SOURCES += src\fonts\SkRemotableFontMgr.cpp
SOURCES += src\fonts\SkTestScalerContext.cpp
HEADERS += src\fonts\SkTestScalerContext.h
SOURCES += src\utils\SkBase64.cpp
HEADERS += src\utils\SkBase64.h
SOURCES += src\utils\SkBitmapHasher.cpp
HEADERS += src\utils\SkBitmapHasher.h
SOURCES += src\utils\SkBitSet.cpp
HEADERS += src\utils\SkBitSet.h
SOURCES += src\utils\SkBoundaryPatch.cpp
SOURCES += src\utils\SkCamera.cpp
SOURCES += src\utils\SkCanvasStack.cpp
HEADERS += src\utils\SkCanvasStack.h
SOURCES += src\utils\SkCanvasStateUtils.cpp
SOURCES += src\utils\SkCondVar.cpp
HEADERS += src\utils\SkCondVar.h
SOURCES += src\utils\SkCubicInterval.cpp
SOURCES += src\utils\SkCullPoints.cpp
SOURCES += src\utils\SkDashPath.cpp
HEADERS += src\utils\SkDashPathPriv.h
SOURCES += src\utils\SkDumpCanvas.cpp
SOURCES += src\utils\SkEventTracer.cpp
HEADERS += src\utils\SkFloatUtils.h
SOURCES += src\utils\SkFrontBufferedStream.cpp
SOURCES += src\utils\SkGatherPixelRefsAndRects.cpp
HEADERS += src\utils\SkGatherPixelRefsAndRects.h
SOURCES += src\utils\SkInterpolator.cpp
SOURCES += src\utils\SkLayer.cpp
SOURCES += src\utils\SkMatrix22.cpp
HEADERS += src\utils\SkMatrix22.h
SOURCES += src\utils\SkMatrix44.cpp
SOURCES += src\utils\SkMD5.cpp
HEADERS += src\utils\SkMD5.h
SOURCES += src\utils\SkMeshUtils.cpp
SOURCES += src\utils\SkNinePatch.cpp
SOURCES += src\utils\SkNullCanvas.cpp
SOURCES += src\utils\SkNWayCanvas.cpp
SOURCES += src\utils\SkOSFile.cpp
SOURCES += src\utils\SkParse.cpp
SOURCES += src\utils\SkParseColor.cpp
SOURCES += src\utils\SkParsePath.cpp
SOURCES += src\utils\SkPatchGrid.cpp
HEADERS += src\utils\SkPatchGrid.h
SOURCES += src\utils\SkPatchUtils.cpp
HEADERS += src\utils\SkPatchUtils.h
SOURCES += src\utils\SkPathUtils.cpp
SOURCES += src\utils\SkPictureUtils.cpp
SOURCES += src\utils\SkProxyCanvas.cpp
SOURCES += src\utils\SkRTConf.cpp
HEADERS += src\utils\SkRunnable.h
SOURCES += src\utils\SkSHA1.cpp
HEADERS += src\utils\SkSHA1.h
SOURCES += src\utils\SkTextureCompressor.cpp
HEADERS += src\utils\SkTextureCompressor.h
SOURCES += src\utils\SkTextureCompressor_ASTC.cpp
HEADERS += src\utils\SkTextureCompressor_ASTC.h
HEADERS += src\utils\SkTextureCompressor_Blitter.h
SOURCES += src\utils\SkTextureCompressor_LATC.cpp
HEADERS += src\utils\SkTextureCompressor_LATC.h
SOURCES += src\utils\SkTextureCompressor_R11EAC.cpp
HEADERS += src\utils\SkTextureCompressor_R11EAC.h
HEADERS += src\utils\SkTFitsIn.h
HEADERS += src\utils\SkThreadPool.h
HEADERS += src\utils\SkThreadUtils.h
SOURCES += src\utils\SkThreadUtils_win.cpp
HEADERS += src\utils\SkThreadUtils_win.h
HEADERS += src\utils\SkTLogic.h
SOURCES += src\utils\win\SkAutoCoInitialize.cpp
SOURCES += src\utils\win\SkHRESULT.cpp
SOURCES += src\utils\win\SkIStream.cpp
SOURCES += src\utils\win\SkWGL_win.cpp
SOURCES += src\core\SkAAClip.cpp
SOURCES += src\core\SkAdvancedTypefaceMetrics.cpp
SOURCES += src\core\SkAlphaRuns.cpp
SOURCES += src\core\SkAnnotation.cpp
HEADERS += src\core\SkAntiRun.h
SOURCES += src\core\SkBBHFactory.cpp
HEADERS += src\core\SkBBoxHierarchy.h
SOURCES += src\core\SkBBoxHierarchyRecord.cpp
HEADERS += src\core\SkBBoxHierarchyRecord.h
SOURCES += src\core\SkBBoxRecord.cpp
HEADERS += src\core\SkBBoxRecord.h
SOURCES += src\core\SkBitmap.cpp
SOURCES += src\core\SkBitmap_scroll.cpp
SOURCES += src\core\SkBitmapCache.cpp
SOURCES += src\core\SkBitmapDevice.cpp
SOURCES += src\core\SkBitmapFilter.cpp
HEADERS += src\core\SkBitmapFilter.h
SOURCES += src\core\SkBitmapHeap.cpp
HEADERS += src\core\SkBitmapHeap.h
SOURCES += src\core\SkBitmapProcShader.cpp
HEADERS += src\core\SkBitmapProcShader.h
SOURCES += src\core\SkBitmapProcState.cpp
HEADERS += src\core\SkBitmapProcState.h
HEADERS += src\core\SkBitmapProcState_matrix.h
SOURCES += src\core\SkBitmapProcState_matrixProcs.cpp
HEADERS += src\core\SkBitmapProcState_sample.h
SOURCES += src\core\SkBitmapScaler.cpp
HEADERS += src\core\SkBitmapScaler.h
HEADERS += src\core\SkBlitBWMaskTemplate.h
SOURCES += src\core\SkBlitMask_D32.cpp
SOURCES += src\core\SkBlitRow_D16.cpp
SOURCES += src\core\SkBlitRow_D32.cpp
SOURCES += src\core\SkBlitter.cpp
HEADERS += src\core\SkBlitter.h
SOURCES += src\core\SkBlitter_A8.cpp
SOURCES += src\core\SkBlitter_ARGB32.cpp
SOURCES += src\core\SkBlitter_RGB16.cpp
SOURCES += src\core\SkBlitter_Sprite.cpp
SOURCES += src\core\SkBuffer.cpp
SOURCES += src\core\SkCanvas.cpp
SOURCES += src\core\SkChunkAlloc.cpp
SOURCES += src\core\SkClipStack.cpp
SOURCES += src\core\SkColor.cpp
SOURCES += src\core\SkColorFilter.cpp
SOURCES += src\core\SkColorTable.cpp
SOURCES += src\core\SkComposeShader.cpp
SOURCES += src\core\SkConfig8888.cpp
HEADERS += src\core\SkConfig8888.h
SOURCES += src\core\SkConvolver.cpp
HEADERS += src\core\SkConvolver.h
HEADERS += src\core\SkCoreBlitters.h
SOURCES += src\core\SkCubicClipper.cpp
HEADERS += src\core\SkCubicClipper.h
SOURCES += src\core\SkData.cpp
SOURCES += src\core\SkDataTable.cpp
SOURCES += src\core\SkDebug.cpp
SOURCES += src\core\SkDeque.cpp
SOURCES += src\core\SkDevice.cpp
SOURCES += src\core\SkDeviceLooper.cpp
SOURCES += src\core\SkDeviceProfile.cpp
SOURCES += src\core\SkDistanceFieldGen.cpp
HEADERS += src\core\SkDistanceFieldGen.h
SOURCES += src\core\SkDither.cpp
SOURCES += src\core\SkDraw.cpp
SOURCES += src\core\SkDrawLooper.cpp
HEADERS += src\core\SkDrawProcs.h
SOURCES += src\core\SkEdge.cpp
HEADERS += src\core\SkEdge.h
SOURCES += src\core\SkEdgeBuilder.cpp
SOURCES += src\core\SkEdgeClipper.cpp
SOURCES += src\core\SkError.cpp
HEADERS += src\core\SkErrorInternals.h
SOURCES += src\core\SkFilterProc.cpp
HEADERS += src\core\SkFilterProc.h
SOURCES += src\core\SkFilterShader.cpp
SOURCES += src\core\SkFlattenable.cpp
SOURCES += src\core\SkFlattenableSerialization.cpp
SOURCES += src\core\SkFloat.cpp
HEADERS += src\core\SkFloat.h
SOURCES += src\core\SkFloatBits.cpp
SOURCES += src\core\SkFont.cpp
SOURCES += src\core\SkFontDescriptor.cpp
HEADERS += src\core\SkFontDescriptor.h
SOURCES += src\core\SkFontHost.cpp
SOURCES += src\core\SkFontStream.cpp
HEADERS += src\core\SkFontStream.h
SOURCES += src\core\SkGeometry.cpp
SOURCES += src\core\SkGlyphCache.cpp
HEADERS += src\core\SkGlyphCache.h
HEADERS += src\core\SkGlyphCache_Globals.h
SOURCES += src\core\SkGraphics.cpp
SOURCES += src\core\SkImageFilter.cpp
SOURCES += src\core\SkImageGenerator.cpp
SOURCES += src\core\SkImageInfo.cpp
SOURCES += src\core\SkInstCnt.cpp
SOURCES += src\core\SkLineClipper.cpp
SOURCES += src\core\SkLocalMatrixShader.cpp
SOURCES += src\core\SkMallocPixelRef.cpp
SOURCES += src\core\SkMask.cpp
SOURCES += src\core\SkMaskFilter.cpp
SOURCES += src\core\SkMaskGamma.cpp
HEADERS += src\core\SkMaskGamma.h
SOURCES += src\core\SkMath.cpp
SOURCES += src\core\SkMatrix.cpp
HEADERS += src\core\SkMessageBus.h
SOURCES += src\core\SkMetaData.cpp
SOURCES += src\core\SkMipMap.cpp
SOURCES += src\core\SkMultiPictureDraw.cpp
SOURCES += src\core\SkPackBits.cpp
SOURCES += src\core\SkPaint.cpp
SOURCES += src\core\SkPaintPriv.cpp
HEADERS += src\core\SkPaintPriv.h
SOURCES += src\core\SkPath.cpp
SOURCES += src\core\SkPathEffect.cpp
SOURCES += src\core\SkPathHeap.cpp
HEADERS += src\core\SkPathHeap.h
SOURCES += src\core\SkPathMeasure.cpp
SOURCES += src\core\SkPathRef.cpp
SOURCES += src\core\SkPicture.cpp
SOURCES += src\core\SkPictureContentInfo.cpp
HEADERS += src\core\SkPictureContentInfo.h
SOURCES += src\core\SkPictureData.cpp
HEADERS += src\core\SkPictureData.h
SOURCES += src\core\SkPictureFlat.cpp
HEADERS += src\core\SkPictureFlat.h
SOURCES += src\core\SkPicturePlayback.cpp
HEADERS += src\core\SkPicturePlayback.h
SOURCES += src\core\SkPictureRecord.cpp
HEADERS += src\core\SkPictureRecord.h
SOURCES += src\core\SkPictureRecorder.cpp
SOURCES += src\core\SkPictureShader.cpp
HEADERS += src\core\SkPictureShader.h
SOURCES += src\core\SkPictureStateTree.cpp
HEADERS += src\core\SkPictureStateTree.h
SOURCES += src\core\SkPixelRef.cpp
SOURCES += src\core\SkPoint.cpp
SOURCES += src\core\SkProcSpriteBlitter.cpp
SOURCES += src\core\SkPtrRecorder.cpp
SOURCES += src\core\SkQuadClipper.cpp
HEADERS += src\core\SkQuadClipper.h
SOURCES += src\core\SkRasterClip.cpp
SOURCES += src\core\SkRasterizer.cpp
SOURCES += src\core\SkReadBuffer.cpp
HEADERS += src\core\SkReadBuffer.h
HEADERS += src\core\SkReader32.h
SOURCES += src\core\SkRecordDraw.cpp
SOURCES += src\core\SkRecorder.cpp
SOURCES += src\core\SkRecording.cpp
SOURCES += src\core\SkRecordOpts.cpp
SOURCES += src\core\SkRect.cpp
SOURCES += src\core\SkRefDict.cpp
SOURCES += src\core\SkRegion.cpp
SOURCES += src\core\SkRegion_path.cpp
HEADERS += src\core\SkRegionPriv.h
SOURCES += src\core\SkRRect.cpp
SOURCES += src\core\SkRTree.cpp
HEADERS += src\core\SkRTree.h
SOURCES += src\core\SkScalar.cpp
SOURCES += src\core\SkScalerContext.cpp
HEADERS += src\core\SkScalerContext.h
SOURCES += src\core\SkScan.cpp
HEADERS += src\core\SkScan.h
SOURCES += src\core\SkScan_Antihair.cpp
SOURCES += src\core\SkScan_AntiPath.cpp
SOURCES += src\core\SkScan_Hairline.cpp
SOURCES += src\core\SkScan_Path.cpp
HEADERS += src\core\SkScanPriv.h
SOURCES += src\core\SkShader.cpp
HEADERS += src\core\SkSinTable.h
HEADERS += src\core\SkSpriteBlitter.h
SOURCES += src\core\SkSpriteBlitter_ARGB32.cpp
SOURCES += src\core\SkSpriteBlitter_RGB16.cpp
HEADERS += src\core\SkSpriteBlitterTemplate.h
SOURCES += src\core\SkStream.cpp
HEADERS += src\core\SkStreamPriv.h
SOURCES += src\core\SkString.cpp
SOURCES += src\core\SkStringUtils.cpp
SOURCES += src\core\SkStroke.cpp
HEADERS += src\core\SkStroke.h
SOURCES += src\core\SkStrokeRec.cpp
SOURCES += src\core\SkStrokerPriv.cpp
HEADERS += src\core\SkStrokerPriv.h
SOURCES += src\core\SkTextBlob.cpp
HEADERS += src\core\SkTextFormatParams.h
HEADERS += src\core\SkTextMapStateProc.h
SOURCES += src\core\SkTileGrid.cpp
HEADERS += src\core\SkTileGrid.h
HEADERS += src\core\SkTLList.h
SOURCES += src\core\SkTLS.cpp
HEADERS += src\core\SkTraceEvent.h
SOURCES += src\core\SkTSearch.cpp
HEADERS += src\core\SkTSort.h
SOURCES += src\core\SkTypeface.cpp
SOURCES += src\core\SkTypefaceCache.cpp
HEADERS += src\core\SkTypefaceCache.h
SOURCES += src\core\SkUnPreMultiply.cpp
SOURCES += src\core\SkUtils.cpp
SOURCES += src\core\SkValidatingReadBuffer.cpp
SOURCES += src\core\SkVertState.cpp
SOURCES += src\core\SkWriteBuffer.cpp
SOURCES += src\core\SkWriter32.cpp
SOURCES += src\core\SkXfermode.cpp
SOURCES += src\core\SkResourceCache.cpp
HEADERS += src\core\SkResourceCache.h

SOURCES += src\doc\SkDocument.cpp
SOURCES += src\image\SkImage.cpp
SOURCES += src\image\SkImage_Raster.cpp
SOURCES += src\image\SkImagePriv.cpp
SOURCES += src\image\SkSurface.cpp
HEADERS += src\image\SkSurface_Base.h
SOURCES += src\image\SkSurface_Raster.cpp
SOURCES += src\lazy\SkCachingPixelRef.cpp
HEADERS += src\lazy\SkCachingPixelRef.h
SOURCES += src\lazy\SkDiscardableMemoryPool.cpp
SOURCES += src\lazy\SkDiscardablePixelRef.cpp
SOURCES += src\pathops\SkAddIntersections.cpp
HEADERS += src\pathops\SkAddIntersections.h
SOURCES += src\pathops\SkDCubicIntersection.cpp
SOURCES += src\pathops\SkDCubicLineIntersection.cpp
SOURCES += src\pathops\SkDCubicToQuads.cpp
SOURCES += src\pathops\SkDLineIntersection.cpp
SOURCES += src\pathops\SkDQuadImplicit.cpp
HEADERS += src\pathops\SkDQuadImplicit.h
SOURCES += src\pathops\SkDQuadIntersection.cpp
SOURCES += src\pathops\SkDQuadLineIntersection.cpp
HEADERS += src\pathops\SkIntersectionHelper.h
SOURCES += src\pathops\SkIntersections.cpp
HEADERS += src\pathops\SkIntersections.h
HEADERS += src\pathops\SkLineParameters.h
SOURCES += src\pathops\SkOpAngle.cpp
HEADERS += src\pathops\SkOpAngle.h
SOURCES += src\pathops\SkOpContour.cpp
HEADERS += src\pathops\SkOpContour.h
SOURCES += src\pathops\SkOpEdgeBuilder.cpp
HEADERS += src\pathops\SkOpEdgeBuilder.h
SOURCES += src\pathops\SkOpSegment.cpp
HEADERS += src\pathops\SkOpSegment.h
HEADERS += src\pathops\SkOpSpan.h
SOURCES += src\pathops\SkPathOpsBounds.cpp
HEADERS += src\pathops\SkPathOpsBounds.h
SOURCES += src\pathops\SkPathOpsCommon.cpp
HEADERS += src\pathops\SkPathOpsCommon.h
SOURCES += src\pathops\SkPathOpsCubic.cpp
HEADERS += src\pathops\SkPathOpsCubic.h
HEADERS += src\pathops\SkPathOpsCurve.h
SOURCES += src\pathops\SkPathOpsDebug.cpp
HEADERS += src\pathops\SkPathOpsDebug.h
SOURCES += src\pathops\SkPathOpsLine.cpp
HEADERS += src\pathops\SkPathOpsLine.h
SOURCES += src\pathops\SkPathOpsOp.cpp
SOURCES += src\pathops\SkPathOpsPoint.cpp
HEADERS += src\pathops\SkPathOpsPoint.h
SOURCES += src\pathops\SkPathOpsQuad.cpp
HEADERS += src\pathops\SkPathOpsQuad.h
SOURCES += src\pathops\SkPathOpsRect.cpp
HEADERS += src\pathops\SkPathOpsRect.h
SOURCES += src\pathops\SkPathOpsSimplify.cpp
SOURCES += src\pathops\SkPathOpsTightBounds.cpp
SOURCES += src\pathops\SkPathOpsTriangle.cpp
HEADERS += src\pathops\SkPathOpsTriangle.h
SOURCES += src\pathops\SkPathOpsTypes.cpp
HEADERS += src\pathops\SkPathOpsTypes.h
SOURCES += src\pathops\SkPathWriter.cpp
HEADERS += src\pathops\SkPathWriter.h
SOURCES += src\pathops\SkQuarticRoot.cpp
HEADERS += src\pathops\SkQuarticRoot.h
SOURCES += src\pathops\SkReduceOrder.cpp
HEADERS += src\pathops\SkReduceOrder.h
SOURCES += src\effects\Sk1DPathEffect.cpp
SOURCES += src\effects\Sk2DPathEffect.cpp
SOURCES += src\effects\SkAlphaThresholdFilter.cpp
SOURCES += src\effects\SkArithmeticMode.cpp
SOURCES += src\effects\SkAvoidXfermode.cpp
SOURCES += src\effects\SkBitmapSource.cpp
SOURCES += src\effects\SkBlurDrawLooper.cpp
SOURCES += src\effects\SkBlurImageFilter.cpp
SOURCES += src\effects\SkBlurMask.cpp
HEADERS += src\effects\SkBlurMask.h
SOURCES += src\effects\SkBlurMaskFilter.cpp
SOURCES += src\effects\SkColorFilterImageFilter.cpp
SOURCES += src\effects\SkColorFilters.cpp
SOURCES += src\effects\SkColorMatrix.cpp
SOURCES += src\effects\SkColorMatrixFilter.cpp
SOURCES += src\effects\SkComposeImageFilter.cpp
SOURCES += src\effects\SkCornerPathEffect.cpp
SOURCES += src\effects\SkDashPathEffect.cpp
SOURCES += src\effects\SkDiscretePathEffect.cpp
SOURCES += src\effects\SkDisplacementMapEffect.cpp
SOURCES += src\effects\SkDropShadowImageFilter.cpp
SOURCES += src\effects\SkEmbossMask.cpp
HEADERS += src\effects\SkEmbossMask.h
HEADERS += src\effects\SkEmbossMask_Table.h
SOURCES += src\effects\SkEmbossMaskFilter.cpp
SOURCES += src\effects\SkGpuBlurUtils.cpp
HEADERS += src\effects\SkGpuBlurUtils.h
SOURCES += src\effects\SkLayerDrawLooper.cpp
SOURCES += src\effects\SkLayerRasterizer.cpp
SOURCES += src\effects\SkLerpXfermode.cpp
SOURCES += src\effects\SkLightingImageFilter.cpp
SOURCES += src\effects\SkLumaColorFilter.cpp
SOURCES += src\effects\SkMagnifierImageFilter.cpp
SOURCES += src\effects\SkMatrixConvolutionImageFilter.cpp
SOURCES += src\effects\SkMatrixImageFilter.cpp
SOURCES += src\effects\SkMergeImageFilter.cpp
SOURCES += src\effects\SkMorphologyImageFilter.cpp
SOURCES += src\effects\SkOffsetImageFilter.cpp
SOURCES += src\effects\SkPaintFlagsDrawFilter.cpp
SOURCES += src\effects\SkPerlinNoiseShader.cpp
SOURCES += src\effects\SkPictureImageFilter.cpp
SOURCES += src\effects\SkPixelXorXfermode.cpp
SOURCES += src\effects\SkPorterDuff.cpp
SOURCES += src\effects\SkRectShaderImageFilter.cpp
SOURCES += src\effects\SkTableColorFilter.cpp
SOURCES += src\effects\SkTableMaskFilter.cpp
SOURCES += src\effects\SkTestImageFilters.cpp
SOURCES += src\effects\SkTileImageFilter.cpp
SOURCES += src\effects\SkTransparentShader.cpp
SOURCES += src\effects\SkXfermodeImageFilter.cpp
SOURCES += src\effects\gradients\SkClampRange.cpp
HEADERS += src\effects\gradients\SkClampRange.h
SOURCES += src\effects\gradients\SkGradientBitmapCache.cpp
HEADERS += src\effects\gradients\SkGradientBitmapCache.h
SOURCES += src\effects\gradients\SkGradientShader.cpp
HEADERS += src\effects\gradients\SkGradientShaderPriv.h
SOURCES += src\effects\gradients\SkLinearGradient.cpp
HEADERS += src\effects\gradients\SkLinearGradient.h
SOURCES += src\effects\gradients\SkRadialGradient.cpp
HEADERS += src\effects\gradients\SkRadialGradient.h
HEADERS += src\effects\gradients\SkRadialGradient_Table.h
SOURCES += src\effects\gradients\SkSweepGradient.cpp
HEADERS += src\effects\gradients\SkSweepGradient.h
SOURCES += src\effects\gradients\SkTwoPointConicalGradient.cpp
HEADERS += src\effects\gradients\SkTwoPointConicalGradient.h
SOURCES += src\effects\gradients\SkTwoPointConicalGradient_gpu.cpp
HEADERS += src\effects\gradients\SkTwoPointConicalGradient_gpu.h
SOURCES += src\effects\gradients\SkTwoPointRadialGradient.cpp
HEADERS += src\effects\gradients\SkTwoPointRadialGradient.h
SOURCES += src\opts\opts_check_x86.cpp
SOURCES += src\opts\SkBitmapFilter_opts_SSE2.cpp
SOURCES += src\opts\SkBitmapProcState_opts_SSE2.cpp
SOURCES += src\opts\SkBitmapProcState_opts_SSSE3.cpp
SOURCES += src\opts\SkBlitRect_opts_SSE2.cpp
SOURCES += src\opts\SkBlitRow_opts_SSE2.cpp
SOURCES += src\opts\SkBlurImage_opts_SSE2.cpp
SOURCES += src\opts\SkBlurImage_opts_SSE4.cpp
SOURCES += src\opts\SkMorphology_opts_SSE2.cpp
SOURCES += src\opts\SkTextureCompression_opts_none.cpp
SOURCES += src\opts\SkUtils_opts_SSE2.cpp
SOURCES += src\opts\SkXfermode_opts_SSE2.cpp
HEADERS += src\ports\SkAtomics_sync.h
HEADERS += src\ports\SkAtomics_win.h
SOURCES += src\ports\SkDebug_win.cpp
SOURCES += src\ports\SkDiscardableMemory_none.cpp
SOURCES += src\ports\SkFontHost_win.cpp
SOURCES += src\ports\SkGlobalInitialization_default.cpp
SOURCES += src\ports\SkMemory_malloc.cpp
HEADERS += src\ports\SkMutex_win.h
SOURCES += src\ports\SkOSFile_stdio.cpp
SOURCES += src\ports\SkOSFile_win.cpp
SOURCES += src\ports\SkTime_win.cpp
SOURCES += src\ports\SkTLS_win.cpp
SOURCES += src\ports\SkFontMgr_default_gdi.cpp
SOURCES += src\gpu\GrAAConvexPathRenderer.cpp
HEADERS += src\gpu\GrAAConvexPathRenderer.h
SOURCES += src\gpu\GrAAHairLinePathRenderer.cpp
HEADERS += src\gpu\GrAAHairLinePathRenderer.h
SOURCES += src\gpu\GrAARectRenderer.cpp
HEADERS += src\gpu\GrAARectRenderer.h
SOURCES += src\gpu\GrAddPathRenderers_default.cpp
HEADERS += src\gpu\GrAllocator.h
SOURCES += src\gpu\GrAllocPool.cpp
HEADERS += src\gpu\GrAllocPool.h
SOURCES += src\gpu\GrAtlas.cpp
HEADERS += src\gpu\GrAtlas.h
HEADERS += src\gpu\GrBinHashKey.h
SOURCES += src\gpu\GrBitmapTextContext.cpp
HEADERS += src\gpu\GrBitmapTextContext.h
SOURCES += src\gpu\GrBlend.cpp
HEADERS += src\gpu\GrBlend.h
SOURCES += src\gpu\GrBufferAllocPool.cpp
HEADERS += src\gpu\GrBufferAllocPool.h
SOURCES += src\gpu\GrCacheID.cpp
SOURCES += src\gpu\GrClipData.cpp
SOURCES += src\gpu\GrClipMaskCache.cpp
HEADERS += src\gpu\GrClipMaskCache.h
SOURCES += src\gpu\GrClipMaskManager.cpp
HEADERS += src\gpu\GrClipMaskManager.h
SOURCES += src\gpu\GrContext.cpp
SOURCES += src\gpu\GrDefaultPathRenderer.cpp
HEADERS += src\gpu\GrDefaultPathRenderer.h
SOURCES += src\gpu\GrDistanceFieldTextContext.cpp
HEADERS += src\gpu\GrDistanceFieldTextContext.h
SOURCES += src\gpu\GrDrawState.cpp
HEADERS += src\gpu\GrDrawState.h
SOURCES += src\gpu\GrDrawTarget.cpp
HEADERS += src\gpu\GrDrawTarget.h
HEADERS += src\gpu\GrDrawTargetCaps.h
SOURCES += src\gpu\GrFontScaler.cpp
HEADERS += src\gpu\GrGeometryBuffer.h
SOURCES += src\gpu\GrGpu.cpp
HEADERS += src\gpu\GrGpu.h
SOURCES += src\gpu\GrGpuFactory.cpp
SOURCES += src\gpu\GrGpuResource.cpp
HEADERS += src\gpu\GrIndexBuffer.h
SOURCES += src\gpu\GrInOrderDrawBuffer.cpp
HEADERS += src\gpu\GrInOrderDrawBuffer.h
SOURCES += src\gpu\GrLayerCache.cpp
HEADERS += src\gpu\GrLayerCache.h
SOURCES += src\gpu\GrMemoryPool.cpp
HEADERS += src\gpu\GrMemoryPool.h
HEADERS += src\gpu\GrOrderedSet.h
SOURCES += src\gpu\GrOvalRenderer.cpp
HEADERS += src\gpu\GrOvalRenderer.h
SOURCES += src\gpu\GrPaint.cpp
SOURCES += src\gpu\GrPath.cpp
HEADERS += src\gpu\GrPath.h
HEADERS += src\gpu\GrPathRange.h
SOURCES += src\gpu\GrPathRenderer.cpp
HEADERS += src\gpu\GrPathRenderer.h
SOURCES += src\gpu\GrPathRendererChain.cpp
HEADERS += src\gpu\GrPathRendering.h
SOURCES += src\gpu\GrPathUtils.cpp
HEADERS += src\gpu\GrPathUtils.h
SOURCES += src\gpu\GrPictureUtils.cpp
HEADERS += src\gpu\GrPictureUtils.h
HEADERS += src\gpu\GrPlotMgr.h
HEADERS += src\gpu\GrRectanizer.h
SOURCES += src\gpu\GrRectanizer_pow2.cpp
HEADERS += src\gpu\GrRectanizer_pow2.h
SOURCES += src\gpu\GrRectanizer_skyline.cpp
HEADERS += src\gpu\GrRectanizer_skyline.h
HEADERS += src\gpu\GrRedBlackTree.h
SOURCES += src\gpu\GrReducedClip.cpp
HEADERS += src\gpu\GrReducedClip.h
SOURCES += src\gpu\GrRenderTarget.cpp
SOURCES += src\gpu\GrResourceCache.cpp
HEADERS += src\gpu\GrResourceCache.h
SOURCES += src\gpu\GrResourceCache2.cpp
HEADERS += src\gpu\GrResourceCache2.h
SOURCES += src\gpu\GrRODrawState.cpp
HEADERS += src\gpu\GrRODrawState.h
SOURCES += src\gpu\GrSoftwarePathRenderer.cpp
HEADERS += src\gpu\GrSoftwarePathRenderer.h
SOURCES += src\gpu\GrStencil.cpp
HEADERS += src\gpu\GrStencil.h
SOURCES += src\gpu\GrStencilAndCoverPathRenderer.cpp
HEADERS += src\gpu\GrStencilAndCoverPathRenderer.h
SOURCES += src\gpu\GrStencilAndCoverTextContext.cpp
HEADERS += src\gpu\GrStencilAndCoverTextContext.h
SOURCES += src\gpu\GrStencilBuffer.cpp
HEADERS += src\gpu\GrStencilBuffer.h
HEADERS += src\gpu\GrStrokeInfo.h
SOURCES += src\gpu\GrSurface.cpp
SOURCES += src\gpu\GrSWMaskHelper.cpp
HEADERS += src\gpu\GrSWMaskHelper.h
HEADERS += src\gpu\GrTBSearch.h
HEADERS += src\gpu\GrTemplates.h
SOURCES += src\gpu\GrTextContext.cpp
HEADERS += src\gpu\GrTextContext.h
SOURCES += src\gpu\GrTextStrike.cpp
HEADERS += src\gpu\GrTextStrike.h
HEADERS += src\gpu\GrTextStrike_impl.h
SOURCES += src\gpu\GrTexture.cpp
SOURCES += src\gpu\GrTextureAccess.cpp
SOURCES += src\gpu\GrTraceMarker.cpp
HEADERS += src\gpu\GrTraceMarker.h
HEADERS += src\gpu\GrTracing.h
HEADERS += src\gpu\GrVertexBuffer.h
SOURCES += src\gpu\SkGpuDevice.cpp
SOURCES += src\gpu\SkGr.cpp
SOURCES += src\gpu\GrProcessor.cpp
SOURCES += src\gpu\GrProgramElement.cpp
SOURCES += src\gpu\GrGpuResourceRef.cpp
SOURCES += src\gpu\SkGrPixelRef.cpp
SOURCES += src\gpu\SkGrTexturePixelRef.cpp
SOURCES += src\gpu\GrPathRendering.cpp
SOURCES += src\gpu\GrOptDrawState.cpp
HEADERS += src\gpu\GrOptDrawState.h
SOURCES += src\gpu\GrPathRange.cpp
SOURCES += src\gpu\gl\GrGLAssembleInterface.cpp
HEADERS += src\gpu\gl\GrGLAssembleInterface.h
SOURCES += src\gpu\gl\GrGLBufferImpl.cpp
HEADERS += src\gpu\gl\GrGLBufferImpl.h
SOURCES += src\gpu\gl\GrGLCaps.cpp
HEADERS += src\gpu\gl\GrGLCaps.h
SOURCES += src\gpu\gl\GrGLContext.cpp
HEADERS += src\gpu\gl\GrGLContext.h
SOURCES += src\gpu\gl\GrGLCreateNullInterface.cpp
SOURCES += src\gpu\gl\GrGLDefaultInterface_native.cpp
HEADERS += src\gpu\gl\GrGLDefines.h
HEADERS += src\gpu\gl\GrGLEffect.h
SOURCES += src\gpu\gl\GrGLExtensions.cpp
SOURCES += src\gpu\gl\GrGLIndexBuffer.cpp
HEADERS += src\gpu\gl\GrGLIndexBuffer.h
SOURCES += src\gpu\gl\GrGLInterface.cpp
HEADERS += src\gpu\gl\GrGLIRect.h
SOURCES += src\gpu\gl\GrGLNameAllocator.cpp
HEADERS += src\gpu\gl\GrGLNameAllocator.h
SOURCES += src\gpu\gl\GrGLNoOpInterface.cpp
HEADERS += src\gpu\gl\GrGLNoOpInterface.h
SOURCES += src\gpu\gl\GrGLPath.cpp
HEADERS += src\gpu\gl\GrGLPath.h
SOURCES += src\gpu\gl\GrGLPathRange.cpp
HEADERS += src\gpu\gl\GrGLPathRange.h
SOURCES += src\gpu\gl\GrGLPathRendering.cpp
HEADERS += src\gpu\gl\GrGLPathRendering.h
SOURCES += src\gpu\gl\GrGLProgram.cpp
HEADERS += src\gpu\gl\GrGLProgram.h
SOURCES += src\gpu\gl\GrGLProgramDataManager.cpp
HEADERS += src\gpu\gl\GrGLProgramDataManager.h
SOURCES += src\gpu\gl\GrGLProgramDesc.cpp
HEADERS += src\gpu\gl\GrGLProgramDesc.h
SOURCES += src\gpu\gl\GrGLProgramEffects.cpp
HEADERS += src\gpu\gl\GrGLProgramEffects.h
SOURCES += src\gpu\gl\GrGLRenderTarget.cpp
HEADERS += src\gpu\gl\GrGLRenderTarget.h
HEADERS += src\gpu\gl\GrGLShaderVar.h
SOURCES += src\gpu\gl\GrGLSL.cpp
HEADERS += src\gpu\gl\GrGLSL.h
HEADERS += src\gpu\gl\GrGLSL_impl.h
SOURCES += src\gpu\gl\GrGLStencilBuffer.cpp
HEADERS += src\gpu\gl\GrGLStencilBuffer.h
SOURCES += src\gpu\gl\GrGLTexture.cpp
HEADERS += src\gpu\gl\GrGLTexture.h
HEADERS += src\gpu\gl\GrGLUniformHandle.h
SOURCES += src\gpu\gl\GrGLUtil.cpp
HEADERS += src\gpu\gl\GrGLUtil.h
SOURCES += src\gpu\gl\GrGLVertexArray.cpp
HEADERS += src\gpu\gl\GrGLVertexArray.h
SOURCES += src\gpu\gl\GrGLVertexBuffer.cpp
HEADERS += src\gpu\gl\GrGLVertexBuffer.h
HEADERS += src\gpu\gl\GrGLVertexEffect.h
SOURCES += src\gpu\gl\GrGpuGL.cpp
HEADERS += src\gpu\gl\GrGpuGL.h
SOURCES += src\gpu\gl\GrGpuGL_program.cpp
SOURCES += src\gpu\gl\SkGLContextHelper.cpp
SOURCES += src\gpu\gl\SkNullGLContext.cpp
SOURCES += src\gpu\gl\win\GrGLCreateNativeInterface_win.cpp
SOURCES += src\gpu\gl\win\SkNativeGLContext_win.cpp
SOURCES += src\gpu\gl\debug\GrBufferObj.cpp
HEADERS += src\gpu\gl\debug\GrBufferObj.h
SOURCES += src\gpu\gl\debug\GrDebugGL.cpp
HEADERS += src\gpu\gl\debug\GrDebugGL.h
HEADERS += src\gpu\gl\debug\GrFakeRefObj.h
HEADERS += src\gpu\gl\debug\GrFBBindableObj.h
SOURCES += src\gpu\gl\debug\GrFrameBufferObj.cpp
HEADERS += src\gpu\gl\debug\GrFrameBufferObj.h
SOURCES += src\gpu\gl\debug\GrGLCreateDebugInterface.cpp
SOURCES += src\gpu\gl\debug\GrProgramObj.cpp
HEADERS += src\gpu\gl\debug\GrProgramObj.h
HEADERS += src\gpu\gl\debug\GrRenderBufferObj.h
SOURCES += src\gpu\gl\debug\GrShaderObj.cpp
HEADERS += src\gpu\gl\debug\GrShaderObj.h
SOURCES += src\gpu\gl\debug\GrTextureObj.cpp
HEADERS += src\gpu\gl\debug\GrTextureObj.h
SOURCES += src\gpu\gl\debug\GrTextureUnitObj.cpp
HEADERS += src\gpu\gl\debug\GrTextureUnitObj.h
HEADERS += src\gpu\gl\debug\GrVertexArrayObj.h
SOURCES += src\gpu\gl\debug\SkDebugGLContext.cpp
SOURCES += src\gpu\gl\builders\GrGLFragmentShaderBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLFragmentShaderBuilder.h
SOURCES += src\gpu\gl\builders\GrGLGeometryShaderBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLGeometryShaderBuilder.h
SOURCES += src\gpu\gl\builders\GrGLProgramBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLProgramBuilder.h
SOURCES += src\gpu\gl\builders\GrGLShaderBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLShaderBuilder.h
SOURCES += src\gpu\gl\builders\GrGLShaderStringBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLShaderStringBuilder.h
SOURCES += src\gpu\gl\builders\GrGLSLPrettyPrint.cpp
SOURCES += src\gpu\gl\builders\GrGLVertexShaderBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLVertexShaderBuilder.h
SOURCES += src\gpu\gl\builders\GrGLFullProgramBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLFullProgramBuilder.h
SOURCES += src\gpu\gl\builders\GrGLFragmentOnlyProgramBuilder.cpp
HEADERS += src\gpu\gl\builders\GrGLFragmentOnlyProgramBuilder.h

HEADERS += src\gpu\effects\Gr1DKernelEffect.h
SOURCES += src\gpu\effects\GrBezierEffect.cpp
HEADERS += src\gpu\effects\GrBezierEffect.h
SOURCES += src\gpu\effects\GrBicubicEffect.cpp
HEADERS += src\gpu\effects\GrBicubicEffect.h
SOURCES += src\gpu\effects\GrConfigConversionEffect.cpp
HEADERS += src\gpu\effects\GrConfigConversionEffect.h
SOURCES += src\gpu\effects\GrConvexPolyEffect.cpp
HEADERS += src\gpu\effects\GrConvexPolyEffect.h
SOURCES += src\gpu\effects\GrConvolutionEffect.cpp
HEADERS += src\gpu\effects\GrConvolutionEffect.h
SOURCES += src\gpu\effects\GrCustomCoordsTextureEffect.cpp
HEADERS += src\gpu\effects\GrCustomCoordsTextureEffect.h
SOURCES += src\gpu\effects\GrDashingEffect.cpp
HEADERS += src\gpu\effects\GrDashingEffect.h
SOURCES += src\gpu\effects\GrDistanceFieldTextureEffect.cpp
HEADERS += src\gpu\effects\GrDistanceFieldTextureEffect.h
SOURCES += src\gpu\effects\GrDitherEffect.cpp
HEADERS += src\gpu\effects\GrDitherEffect.h
SOURCES += src\gpu\effects\GrMatrixConvolutionEffect.cpp
HEADERS += src\gpu\effects\GrMatrixConvolutionEffect.h
SOURCES += src\gpu\effects\GrOvalEffect.cpp
HEADERS += src\gpu\effects\GrOvalEffect.h
SOURCES += src\gpu\effects\GrRRectEffect.cpp
HEADERS += src\gpu\effects\GrRRectEffect.h
SOURCES += src\gpu\effects\GrSimpleTextureEffect.cpp
HEADERS += src\gpu\effects\GrSimpleTextureEffect.h
SOURCES += src\gpu\effects\GrSingleTextureEffect.cpp
HEADERS += src\gpu\effects\GrSingleTextureEffect.h
SOURCES += src\gpu\effects\GrTextureDomain.cpp
HEADERS += src\gpu\effects\GrTextureDomain.h
SOURCES += src\gpu\effects\GrTextureStripAtlas.cpp
HEADERS += src\gpu\effects\GrTextureStripAtlas.h
SOURCES += src\gpu\effects\GrYUVtoRGBEffect.cpp
HEADERS += src\gpu\effects\GrYUVtoRGBEffect.h
SOURCES += src\sfnt\SkOTTable_name.cpp
SOURCES += src\sfnt\SkOTUtils.cpp
SOURCES += src\images\SkImageDecoder.cpp
SOURCES += src\images\SkImageEncoder.cpp
SOURCES += src\images\SkImageEncoder_Factory.cpp
HEADERS += include\core\SkAdvancedTypefaceMetrics.h
HEADERS += include\core\SkBBHFactory.h
HEADERS += include\core\SkBitmap.h
HEADERS += include\core\SkBitmapDevice.h
HEADERS += include\core\SkBlitRow.h
HEADERS += include\core\SkCanvas.h
HEADERS += include\core\SkChunkAlloc.h
HEADERS += include\core\SkClipStack.h
HEADERS += include\core\SkColor.h
HEADERS += include\core\SkColorFilter.h
HEADERS += include\core\SkColorPriv.h
HEADERS += include\core\SkColorShader.h
HEADERS += include\core\SkComposeShader.h
HEADERS += include\core\SkData.h
HEADERS += include\core\SkDeque.h
HEADERS += include\core\SkDevice.h
HEADERS += include\core\SkDeviceProperties.h
HEADERS += include\core\SkDither.h
HEADERS += include\core\SkDraw.h
HEADERS += include\core\SkDrawFilter.h
HEADERS += include\core\SkDrawLooper.h
HEADERS += include\core\SkEndian.h
HEADERS += include\core\SkError.h
HEADERS += include\core\SkFixed.h
HEADERS += include\core\SkFlattenable.h
HEADERS += include\core\SkFlattenableSerialization.h
HEADERS += include\core\SkFloatBits.h
HEADERS += include\core\SkFloatingPoint.h
HEADERS += include\core\SkFontHost.h
HEADERS += include\core\SkGraphics.h
HEADERS += include\core\SkImage.h
HEADERS += include\core\SkImageDecoder.h
HEADERS += include\core\SkImageEncoder.h
HEADERS += include\core\SkImageFilter.h
HEADERS += include\core\SkImageInfo.h
HEADERS += include\core\SkInstCnt.h
HEADERS += include\core\SkMallocPixelRef.h
HEADERS += include\core\SkMask.h
HEADERS += include\core\SkMaskFilter.h
HEADERS += include\core\SkMath.h
HEADERS += include\core\SkMatrix.h
HEADERS += include\core\SkMetaData.h
HEADERS += include\core\SkMultiPictureDraw.h
HEADERS += include\core\SkOnce.h
HEADERS += include\core\SkOSFile.h
HEADERS += include\core\SkPackBits.h
HEADERS += include\core\SkPaint.h
HEADERS += include\core\SkPath.h
HEADERS += include\core\SkPathEffect.h
HEADERS += include\core\SkPathMeasure.h
HEADERS += include\core\SkPathRef.h
HEADERS += include\core\SkPicture.h
HEADERS += include\core\SkPictureRecorder.h
HEADERS += include\core\SkPixelRef.h
HEADERS += include\core\SkPoint.h
HEADERS += include\core\SkPreConfig.h
HEADERS += include\core\SkRasterizer.h
HEADERS += include\core\SkRect.h
HEADERS += include\core\SkRefCnt.h
HEADERS += include\core\SkRegion.h
HEADERS += include\core\SkRRect.h
HEADERS += include\core\SkScalar.h
HEADERS += include\core\SkShader.h
HEADERS += include\core\SkStream.h
HEADERS += include\core\SkString.h
HEADERS += include\core\SkStrokeRec.h
HEADERS += include\core\SkSurface.h
HEADERS += include\core\SkTArray.h
HEADERS += include\core\SkTDArray.h
HEADERS += include\core\SkTDict.h
HEADERS += include\core\SkTDStack.h
HEADERS += include\core\SkTemplates.h
HEADERS += include\core\SkTextBlob.h
HEADERS += include\core\SkThread.h
HEADERS += include\core\SkTime.h
HEADERS += include\core\SkTInternalLList.h
HEADERS += include\core\SkTLazy.h
HEADERS += include\core\SkTRegistry.h
HEADERS += include\core\SkTSearch.h
HEADERS += include\core\SkTypeface.h
HEADERS += include\core\SkTypes.h
HEADERS += include\core\SkUnPreMultiply.h
HEADERS += include\core\SkUtils.h
HEADERS += include\core\SkWeakRefCnt.h
HEADERS += include\core\SkWriter32.h
HEADERS += include\core\SkXfermode.h
HEADERS += include\utils\SkBoundaryPatch.h
HEADERS += include\utils\SkCamera.h
HEADERS += include\utils\SkCanvasStateUtils.h
HEADERS += include\utils\SkCubicInterval.h
HEADERS += include\utils\SkCullPoints.h
HEADERS += include\utils\SkDebugUtils.h
HEADERS += include\utils\SkDumpCanvas.h
HEADERS += include\utils\SkEventTracer.h
HEADERS += include\utils\SkFrontBufferedStream.h
HEADERS += include\utils\SkInterpolator.h
HEADERS += include\utils\SkLayer.h
HEADERS += include\utils\SkMatrix44.h
HEADERS += include\utils\SkMeshUtils.h
HEADERS += include\utils\SkNinePatch.h
HEADERS += include\utils\SkNoSaveLayerCanvas.h
HEADERS += include\utils\SkNullCanvas.h
HEADERS += include\utils\SkNWayCanvas.h
HEADERS += include\utils\SkParse.h
HEADERS += include\utils\SkParsePaint.h
HEADERS += include\utils\SkParsePath.h
HEADERS += include\utils\SkPictureUtils.h
HEADERS += include\utils\SkProxyCanvas.h
HEADERS += include\utils\SkRandom.h
HEADERS += include\utils\SkRTConf.h
HEADERS += include\utils\SkWGL.h
HEADERS += include\utils\win\SkAutoCoInitialize.h
HEADERS += include\utils\win\SkHRESULT.h
HEADERS += include\utils\win\SkIStream.h
HEADERS += include\utils\win\SkTScopedComPtr.h
HEADERS += include\utils\mac\SkCGUtils.h
HEADERS += include\pathops\SkPathOps.h
HEADERS += include\effects\Sk1DPathEffect.h
HEADERS += include\effects\Sk2DPathEffect.h
HEADERS += include\effects\SkAlphaThresholdFilter.h
HEADERS += include\effects\SkArithmeticMode.h
HEADERS += include\effects\SkAvoidXfermode.h
HEADERS += include\effects\SkBitmapSource.h
HEADERS += include\effects\SkBlurDrawLooper.h
HEADERS += include\effects\SkBlurImageFilter.h
HEADERS += include\effects\SkBlurMaskFilter.h
HEADERS += include\effects\SkColorFilterImageFilter.h
HEADERS += include\effects\SkColorMatrix.h
HEADERS += include\effects\SkColorMatrixFilter.h
HEADERS += include\effects\SkCornerPathEffect.h
HEADERS += include\effects\SkDashPathEffect.h
HEADERS += include\effects\SkDiscretePathEffect.h
HEADERS += include\effects\SkDisplacementMapEffect.h
HEADERS += include\effects\SkDrawExtraPathEffect.h
HEADERS += include\effects\SkDropShadowImageFilter.h
HEADERS += include\effects\SkEmbossMaskFilter.h
HEADERS += include\effects\SkGradientShader.h
HEADERS += include\effects\SkLayerDrawLooper.h
HEADERS += include\effects\SkLayerRasterizer.h
HEADERS += include\effects\SkLerpXfermode.h
HEADERS += include\effects\SkLightingImageFilter.h
HEADERS += include\effects\SkLumaColorFilter.h
HEADERS += include\effects\SkMagnifierImageFilter.h
HEADERS += include\effects\SkMorphologyImageFilter.h
HEADERS += include\effects\SkOffsetImageFilter.h
HEADERS += include\effects\SkPaintFlagsDrawFilter.h
HEADERS += include\effects\SkPerlinNoiseShader.h
HEADERS += include\effects\SkPixelXorXfermode.h
HEADERS += include\effects\SkPorterDuff.h
HEADERS += include\effects\SkRectShaderImageFilter.h
HEADERS += include\effects\SkTableColorFilter.h
HEADERS += include\effects\SkTableMaskFilter.h
HEADERS += include\effects\SkTileImageFilter.h
HEADERS += include\effects\SkTransparentShader.h
HEADERS += include\effects\SkXfermodeImageFilter.h
HEADERS += include\ports\SkFontConfigInterface.h
HEADERS += include\ports\SkFontMgr.h
HEADERS += include\ports\SkFontMgr_indirect.h
HEADERS += include\ports\SkFontStyle.h
HEADERS += include\ports\SkRemotableFontMgr.h
HEADERS += include\gpu\GrBackendEffectFactory.h
HEADERS += include\gpu\GrClipData.h
HEADERS += include\gpu\GrColor.h
HEADERS += include\gpu\GrConfig.h
HEADERS += include\gpu\GrContext.h
HEADERS += include\gpu\GrContextFactory.h
HEADERS += include\gpu\GrCoordTransform.h
HEADERS += include\gpu\GrEffect.h
HEADERS += include\gpu\GrEffectStage.h
HEADERS += include\gpu\GrEffectUnitTest.h
HEADERS += include\gpu\GrFontScaler.h
HEADERS += include\gpu\GrGlyph.h
HEADERS += include\gpu\GrGpuResource.h
HEADERS += include\gpu\GrPaint.h
HEADERS += include\gpu\GrPathRendererChain.h
HEADERS += include\gpu\GrRect.h
HEADERS += include\gpu\GrRenderTarget.h
HEADERS += include\gpu\GrSurface.h
HEADERS += include\gpu\GrTBackendEffectFactory.h
HEADERS += include\gpu\GrTexture.h
HEADERS += include\gpu\GrTextureAccess.h
HEADERS += include\gpu\GrTypes.h
HEADERS += include\gpu\GrUserConfig.h
HEADERS += include\gpu\SkGpuDevice.h
HEADERS += include\gpu\SkGr.h
HEADERS += include\gpu\SkGrPixelRef.h
HEADERS += include\gpu\SkGrTexturePixelRef.h
HEADERS += include\gpu\gl\GrGLConfig.h
HEADERS += include\gpu\gl\GrGLExtensions.h
HEADERS += include\gpu\gl\GrGLFunctions.h
HEADERS += include\gpu\gl\GrGLInterface.h
HEADERS += include\gpu\gl\GrGLSLPrettyPrint.h
HEADERS += include\gpu\gl\SkDebugGLContext.h
HEADERS += include\gpu\gl\SkGLContextHelper.h
HEADERS += include\gpu\gl\SkMesaGLContext.h
HEADERS += include\gpu\gl\SkNativeGLContext.h
HEADERS += include\gpu\gl\SkNullGLContext.h
HEADERS += include\gpu\gl\SkANGLEGLContext.h
HEADERS += src\images\bmpdecoderhelper.h
HEADERS += src\images\SkScaledBitmapSampler.h
HEADERS += src\images\transform_scanline.h
