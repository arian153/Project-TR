/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#pragma once
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d2d1_2.h>
#include <dwrite_2.h>
#include <string>
#include "../../Math/Utility/MathDef.hpp"
#include "../../Core/Utility/CoreDef.hpp"

namespace GAM400
{
    class MatrixManager;
    class Color;

    class RendererDX11
    {
    public:
        RendererDX11();
        ~RendererDX11();

        ID3D11Device*           GetDevice() const;
        ID3D11DeviceContext*    GetDeviceContext() const;
        ID3D11DepthStencilView* GetDepthStencilView() const;
        HWND                    GetHwnd() const;
        ID2D1DeviceContext1*    GetD2DDeviceContext() const;
        IDWriteFactory2*        GetDWWriteFactory() const;
        ID3D11Texture2D*        GetFrameBuffer();

        std::string GetVideoCardInfo(size_t& memory) const;

        void SetHwnd(HWND hwnd);
        void SetBackBufferRenderTarget() const;
        void SetRasterStateWireFrame(bool flag) const;
        void ResetViewport() const;
        void SetUpDWRenderTarget();

    protected:
        void SetUpAdapterDescription(int client_width, int client_height);
        void SetUpDevice();
        void SetUpSwapChain(int client_width, int client_height, bool fullscreen_flag);
        void SetUpBackBuffer();
        void SetUpDepthBufferDescription(int client_width, int client_height);
        void SetUpStencilStateDescription();
        void SetUpDepthStencilViewDescription();
        void SetUpRasterDescription();
        void SetUpViewport(int client_width, int client_height);
        void SetUpMultiSamplingLevel();
        void SetUpBlendState();
        void SetUpDWDevice();

    protected:
        IDXGISwapChain*          m_swap_chain                    = nullptr;
        ID3D11Device*            m_device                        = nullptr;
        ID3D11DeviceContext*     m_device_context                = nullptr;
        ID3D11RenderTargetView*  m_render_target_view            = nullptr;
        ID3D11Texture2D*         m_depth_stencil_buffer          = nullptr;
        ID3D11DepthStencilState* m_depth_stencil_state           = nullptr;
        ID3D11DepthStencilView*  m_depth_stencil_view            = nullptr;
        ID3D11RasterizerState*   m_raster_state                  = nullptr;
        ID3D11RasterizerState*   m_wire_frame_raster_state       = nullptr;
        ID3D11DepthStencilState* m_depth_disabled_stencil_state  = nullptr;
        ID3D11BlendState*        m_alpha_enabled_blending_state  = nullptr;
        ID3D11BlendState*        m_alpha_disabled_blending_state = nullptr;
        ID2D1Device1*            m_d2d_device                    = nullptr;
        ID2D1DeviceContext1*     m_d2d_device_context            = nullptr;
        ID2D1Factory2*           m_d2d_factory                   = nullptr;
        IDWriteFactory2*         m_write_factory                 = nullptr;
        ID2D1Bitmap1*            m_target_bitmap                 = nullptr;
        HWND                     m_hwnd                          = nullptr;
        MatrixManager*           m_matrix_generator              = nullptr;
        D3D_FEATURE_LEVEL        m_d3d_feature_level;
        DXGI_FORMAT              m_dxgi_color_format;
        D3D11_VIEWPORT           m_viewport;
        ID3D11Texture2D*         m_frame_buffer = nullptr;;

        UINT   m_back_buffer_count = 1;
        bool   m_enable_msaa       = false;
        UINT   m_msaa_quality      = 0;
        bool   m_vsync_enabled     = false;
        UINT   m_numerator;
        UINT   m_denominator;
        size_t m_video_card_memory;
        String m_video_card_description;
        size_t m_client_width;
        size_t m_client_height;
        Real   m_dw_dpi = 96.0f;
    };
}
