#include <fast/backends/gfx_rendering_api.h>

class Extractor : public Fast::GfxRenderingAPI {
public:
  Extractor() = default;
  const char* GetName() override {
    return "Extractor";
  }
  int GetMaxTextureSize() override {
    return 0;
  }
  Fast::GfxClipParameters GetClipParameters() override {
    return {false, false};
  }
  void UnloadShader(Fast::ShaderProgram* oldPrg) override {}
  void LoadShader(Fast::ShaderProgram* newPrg) override {}
  void ClearShaderCache() override {}
  Fast::ShaderProgram* CreateAndLoadNewShader(uint64_t shaderId0, uint64_t shaderId1) override {
    return nullptr;
  }
  Fast::ShaderProgram* LookupShader(uint64_t shaderId0, uint64_t shaderId1) override {
    return nullptr;
  }
  void ShaderGetInfo(Fast::ShaderProgram* prg, uint8_t* numInputs, bool usedTextures[2]) override {}
  uint32_t NewTexture() override {
    return 0;
  }
  void SelectTexture(int tile, uint32_t textureId) override {}
  void UploadTexture(const uint8_t* rgba32Buf, uint32_t width, uint32_t height) override {}
  void SetSamplerParameters(int sampler, bool linear_filter, uint32_t cms, uint32_t cmt) override {}
  void SetDepthTestAndMask(bool depth_test, bool z_upd) override {}
  void SetZmodeDecal(bool decal) override {}
  void SetViewport(int x, int y, int width, int height) override {}
  void SetScissor(int x, int y, int width, int height) override {}
  void SetUseAlpha(bool useAlpha) override {}
  void DrawTriangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) override {}
  void Init() override {}
  void OnResize() override {}
  void StartFrame() override {}
  void EndFrame() override {}
  void FinishRender() override {}
  int CreateFramebuffer() override {
    return 0;
  }
  void UpdateFramebufferParameters(int fb_id, uint32_t width, uint32_t height, uint32_t msaa_level,
                                    bool opengl_invertY, bool render_target, bool has_depth_buffer,
                                    bool can_extract_depth) override {}
  void StartDrawToFramebuffer(int fbId, float noiseScale) override {}
  void CopyFramebuffer(int fbDstId, int fbSrcId, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0,
                        int dstY0, int dstX1, int dstY1) override {}
  void ClearFramebuffer(bool color, bool depth) override {}
  void ReadFramebufferToCPU(int fbId, uint32_t width, uint32_t height, uint16_t* rgba16Buf) override {}
  void ResolveMSAAColorBuffer(int fbIdTarger, int fbIdSrc) override {}
  std::unordered_map<std::pair<float, float>, uint16_t, Fast::hash_pair_ff> GetPixelDepth(int fb_id, const std::set<std::pair<float, float>>& coordinates) override {
    return {};
  }
  void* GetFramebufferTextureId(int fbId) override {
    return nullptr;
  }
  void SelectTextureFb(int fbId) override {}
  void DeleteTexture(uint32_t texId) override {}
  void SetTextureFilter(Fast::FilteringMode mode) override {}
  Fast::FilteringMode GetTextureFilter() override {
    return Fast::FilteringMode::FILTER_NONE;
  }
  void SetSrgbMode() override {}
  ImTextureID GetTextureById(int id) override {
    return nullptr;
  }
  void SetCurrentPrimDepth(float depth) override {}
};


