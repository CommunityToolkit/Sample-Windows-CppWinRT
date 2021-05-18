#pragma once

#include "MainPage.g.h"
#include "winrt/CSharpIslandRuntimeComponent.h"
#include "winrt/CSharpIslandRuntimeComponent.CSharpIslandRuntimeComponent_XamlTypeInfo.h"

namespace winrt::CppWinRTToolkitIsland::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::CppWinRTToolkitIsland::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
