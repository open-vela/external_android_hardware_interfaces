/**
 * Copyright (c) 2021, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// TODO(b/129481165): remove the #pragma below and fix conversion issues
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

#include <GraphicsComposerCallback.h>
#include <aidl/android/hardware/graphics/composer3/IComposerClient.h>
#include <android-base/unique_fd.h>
#include <android/hardware/graphics/composer3/command-buffer.h>
#include <mapper-vts/2.1/MapperVts.h>
#include <renderengine/RenderEngine.h>
#include <ui/GraphicBuffer.h>

#include <memory>

// TODO(b/129481165): remove the #pragma below and fix conversion issues
#pragma clang diagnostic pop  // ignored "-Wconversion

namespace aidl::android::hardware::graphics::composer3::vts {

using ::android::renderengine::LayerSettings;
using common::Dataspace;
using common::PixelFormat;
using IMapper2_1 = ::android::hardware::graphics::mapper::V2_1::IMapper;

static const Color BLACK = {0, 0, 0, static_cast<int8_t>(0xff)};
static const Color RED = {static_cast<int8_t>(0xff), 0, 0, static_cast<int8_t>(0xff)};
static const Color TRANSLUCENT_RED = {static_cast<int8_t>(0xff), 0, 0, 0x33};
static const Color GREEN = {0, static_cast<int8_t>(0xff), 0, static_cast<int8_t>(0xff)};
static const Color BLUE = {0, 0, static_cast<int8_t>(0xff), static_cast<int8_t>(0xff)};
static const Color WHITE = {static_cast<int8_t>(0xff), static_cast<int8_t>(0xff),
                            static_cast<int8_t>(0xff), static_cast<int8_t>(0xff)};

class TestRenderEngine;

class TestLayer {
  public:
    TestLayer(const std::shared_ptr<IComposerClient>& client, int64_t display)
        : mDisplay(display), mComposerClient(client) {
        client->createLayer(display, kBufferSlotCount, &mLayer);
    }

    // ComposerClient will take care of destroying layers, no need to explicitly
    // call destroyLayers here
    virtual ~TestLayer(){};

    virtual void write(CommandWriterBase& writer);
    virtual LayerSettings toRenderEngineLayerSettings();

    void setDisplayFrame(Rect frame) { mDisplayFrame = frame; }
    void setSourceCrop(FRect crop) { mSourceCrop = crop; }
    void setZOrder(uint32_t z) { mZOrder = z; }

    void setSurfaceDamage(std::vector<Rect> surfaceDamage) {
        mSurfaceDamage = std::move(surfaceDamage);
    }

    void setTransform(Transform transform) { mTransform = transform; }
    void setAlpha(float alpha) { mAlpha = alpha; }
    void setBlendMode(BlendMode blendMode) { mBlendMode = blendMode; }

    BlendMode getBlendMode() const { return mBlendMode; }

    uint32_t getZOrder() const { return mZOrder; }

    float getAlpha() const { return mAlpha; }

    int64_t getLayer() const { return mLayer; }

  protected:
    int64_t mDisplay;
    int64_t mLayer;
    Rect mDisplayFrame = {0, 0, 0, 0};
    std::vector<Rect> mSurfaceDamage;
    Transform mTransform = static_cast<Transform>(0);
    FRect mSourceCrop = {0, 0, 0, 0};
    static constexpr uint32_t kBufferSlotCount = 64;
    float mAlpha = 1.0;
    BlendMode mBlendMode = BlendMode::NONE;
    uint32_t mZOrder = 0;

  private:
    std::shared_ptr<IComposerClient> const mComposerClient;
};

class TestColorLayer : public TestLayer {
  public:
    TestColorLayer(const std::shared_ptr<IComposerClient>& client, int64_t display)
        : TestLayer{client, display} {}

    void write(CommandWriterBase& writer) override;

    LayerSettings toRenderEngineLayerSettings() override;

    void setColor(Color color) { mColor = color; }

  private:
    Color mColor = WHITE;
};

class TestBufferLayer : public TestLayer {
  public:
    TestBufferLayer(const std::shared_ptr<IComposerClient>& client,
                    const ::android::sp<::android::GraphicBuffer>& graphicBuffer,
                    TestRenderEngine& renderEngine, int64_t display, uint32_t width,
                    uint32_t height, common::PixelFormat format,
                    Composition composition = Composition::DEVICE);

    void write(CommandWriterBase& writer) override;

    LayerSettings toRenderEngineLayerSettings() override;

    void fillBuffer(std::vector<Color>& expectedColors);

    void setBuffer(std::vector<Color> colors);

    void setDataspace(Dataspace dataspace, CommandWriterBase& writer);

    void setToClientComposition(CommandWriterBase& writer);

    uint32_t getWidth() const { return mWidth; }

    uint32_t getHeight() const { return mHeight; }

    ::android::Rect getAccessRegion() const { return mAccessRegion; }

    uint32_t getLayerCount() const { return mLayerCount; }

  protected:
    Composition mComposition;
    ::android::sp<::android::GraphicBuffer> mGraphicBuffer;
    TestRenderEngine& mRenderEngine;
    int32_t mFillFence;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mLayerCount;
    PixelFormat mPixelFormat;
    uint32_t mUsage;
    uint32_t mStride;
    ::android::Rect mAccessRegion;
};

class ReadbackHelper {
  public:
    static std::string getColorModeString(ColorMode mode);

    static std::string getDataspaceString(Dataspace dataspace);

    static Dataspace getDataspaceForColorMode(ColorMode mode);

    static int32_t GetBytesPerPixel(PixelFormat pixelFormat);

    static void fillBuffer(uint32_t width, uint32_t height, uint32_t stride, void* bufferData,
                           PixelFormat pixelFormat, std::vector<Color> desiredPixelColors);

    static void clearColors(std::vector<Color>& expectedColors, int32_t width, int32_t height,
                            int32_t displayWidth);

    static void fillColorsArea(std::vector<Color>& expectedColors, int32_t stride, Rect area,
                               Color color);

    static bool readbackSupported(const PixelFormat& pixelFormat, const Dataspace& dataspace);

    static const std::vector<ColorMode> colorModes;
    static const std::vector<Dataspace> dataspaces;

    static void compareColorBuffers(std::vector<Color>& expectedColors, void* bufferData,
                                    const int32_t stride, const uint32_t width,
                                    const uint32_t height, PixelFormat pixelFormat);
};

class ReadbackBuffer {
  public:
    ReadbackBuffer(int64_t display, const std::shared_ptr<IComposerClient>& client,
                   const ::android::sp<::android::GraphicBuffer>& graphicBuffer, int32_t width,
                   int32_t height, common::PixelFormat pixelFormat, common::Dataspace dataspace);

    void setReadbackBuffer();

    void checkReadbackBuffer(std::vector<Color> expectedColors);

    ::android::sp<::android::GraphicBuffer> allocate();

  protected:
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mLayerCount;
    uint32_t mUsage;
    uint32_t mStride;
    PixelFormat mPixelFormat;
    Dataspace mDataspace;
    int64_t mDisplay;
    ::android::sp<::android::GraphicBuffer> mGraphicBuffer;
    std::shared_ptr<IComposerClient> mComposerClient;
    ::android::Rect mAccessRegion;
    native_handle_t mBufferHandle;
};

}  // namespace aidl::android::hardware::graphics::composer3::vts
