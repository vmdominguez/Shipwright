#include <fast/backends/gfx_window_manager_api.h>

class FakeWindowBackend : public Fast::GfxWindowBackend {
public:
  FakeWindowBackend() = default;
  void Init(const char* gameName, const char* apiName, bool startFullScreen, uint32_t width, uint32_t height, int32_t posX, int32_t posY) override {}
  void Close() override {}
  void SetKeyboardCallbacks(bool (*mOnKeyDown)(int scancode), bool (*mOnKeyUp)(int scancode), void (*mOnAllKeysUp)()) override {}
  void SetMouseCallbacks(bool (*mOnMouseButtonDown)(int btn), bool (*mOnMouseButtonUp)(int btn)) override {}
  void SetFullscreenChangedCallback(void (*mOnFullscreenChanged)(bool is_now_fullscreen)) override {}
  void SetFullscreen(bool fullscreen) override {}
  void GetActiveWindowRefreshRate(uint32_t* refreshRate) override {}
  void SetCursorVisibility(bool visability) override {}
  void SetMousePos(int32_t posX, int32_t posY) override {}
  void GetMousePos(int32_t* x, int32_t* y) override {}
  void GetMouseDelta(int32_t* x, int32_t* y) override {}
  void GetMouseWheel(float* x, float* y) override {}
  bool GetMouseState(uint32_t btn) override {
    return false;
  }
  void SetMouseCapture(bool capture) override {}
  bool IsMouseCaptured() override {
    return false;
  }
  void GetDimensions(uint32_t* width, uint32_t* height, int32_t* posX, int32_t* posY) override {}
  void SetDimensions(uint32_t width, uint32_t height, int32_t posX, int32_t posY) override {}
  Ship::WindowRect GetPrimaryMonitorRect() override {
    return {0,0,0,0};
  }
  void HandleEvents() override {}
  bool IsFrameReady() override {
    return false;
  }
  void SwapBuffersBegin() override {}
  void SwapBuffersEnd() override {}
  double GetTime() override {
    return 0;
  }
  int GetTargetFps() override {
    return 0;
  }
  void SetTargetFps(int fps) override {}
  void SetMaxFrameLatency(int latency) override {}
  const char* GetKeyName(int scancode) override {
    return "";
  }
  bool CanDisableVsync() override {
    return false;
  }
  bool IsRunning() override {
    return true;
  }
  void Destroy() override {}
  bool IsFullscreen() override {
    return false;
  }
};
