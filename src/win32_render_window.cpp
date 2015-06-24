#include <core/render_window.h>

#include <core/render_system.h>
#include <core/win32_error_handler.h>
#include <core/win32_hinstance.h>
#include <core/win32_wndproc.h>

#include <ctime>
#include <string>

#include <Windows.h>

namespace opengl_core
{
  struct render_window::window_impl
  {
    HWND m_window;
    WNDCLASS m_window_class;
    static unsigned int s_window_count;

    window_impl() :
      m_window(0),
      m_window_class()
    {}
  };

  unsigned int render_window::window_impl::s_window_count = 0;

  render_window::render_window() :
    m_impl(new render_window::window_impl)
  {
    srand((unsigned int)time(nullptr));
    std::wstring cname = L"render_window";
    cname += ('0' + (wchar_t)(window_impl::s_window_count++));
    const wchar_t *class_name = cname.c_str();

    m_impl->m_window_class.hCursor = NULL;
    m_impl->m_window_class.lpszMenuName = NULL;
    m_impl->m_window_class.lpszClassName = (class_name);
    m_impl->m_window_class.hbrBackground = NULL;
    m_impl->m_window_class.hInstance = win32_hinstance::acquire();
    m_impl->m_window_class.style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
    m_impl->m_window_class.lpfnWndProc = wnd_proc;
    m_impl->m_window_class.cbWndExtra = 0;
    m_impl->m_window_class.cbClsExtra = 0;

    if (!::RegisterClass(&m_impl->m_window_class)) {
      print_last_error_and_assert();
    }

    m_impl->m_window = ::CreateWindowEx(0, m_impl->m_window_class.lpszClassName,
      L"", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL, win32_hinstance::acquire(), nullptr);
    if (!m_impl->m_window) {
      print_last_error_and_assert();
    }
  }

  render_window::~render_window()
  {
    delete m_impl;
  }

  void render_window::init(render_system &system, fb_config &fbc)
  {
    ShowWindow(m_impl->m_window, SW_HIDE);
    destroy();

    std::wstring cname = L"render_window";
    cname += ('0' + (wchar_t)(window_impl::s_window_count++));
    const wchar_t *class_name = cname.c_str();

    m_impl->m_window_class.hCursor = NULL;
    m_impl->m_window_class.lpszMenuName = NULL;
    m_impl->m_window_class.lpszClassName = (class_name);
    m_impl->m_window_class.hbrBackground = NULL;
    m_impl->m_window_class.hInstance = win32_hinstance::acquire();
    m_impl->m_window_class.style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
    m_impl->m_window_class.lpfnWndProc = wnd_proc;
    m_impl->m_window_class.cbWndExtra = 0;
    m_impl->m_window_class.cbClsExtra = 0;

    if (!::RegisterClass(&m_impl->m_window_class)) {
      print_last_error_and_assert();
    }

    m_impl->m_window = ::CreateWindowEx(0, m_impl->m_window_class.lpszClassName,
      L"", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL, win32_hinstance::acquire(), &system);
    if (!m_impl->m_window) {
      print_last_error_and_assert();
    }
  }

  void render_window::map()
  {
    STARTUPINFO startupInfo;
    ::GetStartupInfo(&startupInfo);
    int cmdShow = (startupInfo.dwFlags & STARTF_USESHOWWINDOW) ?
      startupInfo.wShowWindow : SW_SHOWDEFAULT;
    if (!::ShowWindow(m_impl->m_window, cmdShow)) {
      print_last_error();
    }

    if (!::UpdateWindow(m_impl->m_window)) {
      print_last_error();
    }
  }

  void render_window::destroy()
  {
    if (!::ReleaseDC(m_impl->m_window, ::GetDC(m_impl->m_window))) {
      print_last_error();
    }

    if (!::DestroyWindow(m_impl->m_window)) {
      print_last_error();
    }

    if (!::UnregisterClass(m_impl->m_window_class.lpszClassName,
      win32_hinstance::acquire())) {
      print_last_error();
    }
  }

  void *render_window::impl()
  {
    return (void*)(&(m_impl->m_window));
  }
}
