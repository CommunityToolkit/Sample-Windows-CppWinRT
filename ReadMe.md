# C# Island 🏝 in C++/WinRT Sample

This project demonstrates how to use the [Windows Community Toolkit](https://aka.ms/windowstoolkit) controls from within a "C# Island" in a [C++/WinRT](https://aka.ms/cppwinrt) UWP app. It's important to note that there are 🐉 Dragons 🐉 here, there's not direct tooling support for this with a lot of manual configuration needed to proceed.

A brief explanation of what this project does can be found in this [🦙 Learnings video](https://www.twitch.tv/videos/1088935076). Read more details below.

## Running the Project

⚠ **Warning**: The project must be run in Release mode (or with .NET Native compilation turned on), see https://github.com/microsoft/microsoft-ui-xaml/issues/5040. Otherwise, you should be able to set the `CppWinRTToolkitIsland` as the startup project and run it in **Release** mode with the `x64` architecture easily from cloning.

⚠ **Warning**: Some configuration in the vcxproj file is SDK installed version dependent, be sure to [follow these docs steps](https://docs.microsoft.com/windows/uwp/cpp-and-winrt-apis/use-csharp-component-from-cpp-winrt#configure-for-windows-10-fall-creators-update-100-build-16299) on your machine if the default setup in this provided project doesn't work.

```xml
    <DotNetNativeVersion>2.2.10-rel-29722-00</DotNetNativeVersion>
    <DotNetNativeSharedLibary>2.2.8-rel-29722-00</DotNetNativeSharedLibary>
    <UWPCoreRuntimeSdkVersion>2.2.12</UWPCoreRuntimeSdkVersion>
```

📝 _Note_: NuGet doesn't automatically pull dependencies for the C# project, we have had to manually copy the dlls to the `dlls` folder here and added to our `vcxproj` file to copy them to the application's output directory. We're using the released 7.0.2 versions of the Windows Community Toolkit in this project.

```xml
    <None Include="$(SolutionDir)dlls\**\*.*">
      <Link>%(RecursiveDir)%(Filename)%(Extension)</Link>
      <DeploymentContent>true</DeploymentContent>
    </None>
```

## Project Background

The Windows Community Toolkit is a .NET component library. It's UWP controls are all UWP Class Libraries and _not_ Windows Runtime Components. Windows Runtime Components (WRC) are what let a developer write a component that can be used in any UWP project regardless of language, i.e. C#, C++/WinRT, etc... Since, the Toolkit doesn't use WRC, it can't be directly leveraged by a C++/WinRT application. (We don't use WRC in the Toolkit as the extra restrictions they impose make it hard to create an extensible API surface.)

Some developers don't want to reference C# WRC components as it does pull in the _.NET runtime_ as a requirement to run their app and adds extra performance and memory concerns. However, at times, it's still easier to use a pre-built component that already performs the functionality that you may need.

Therefore, we wanted to create this sample to demonstrate how you can leverage a Toolkit control within a C++/WinRT application. This is done by 'wrapping' the Toolkit's code within its own C# Windows Runtime Component project. As long as no types from the Toolkit are exposed, this WRC can act as a bridge (or Island 🏝) between the Toolkit components and the application.

It consists of two projects, the C++/WinRT application itself, and a new C# Windows Runtime Component. The WRC project houses a page which hosts the controls of the Toolkit within a custom UserControl. This UserControl (as a WRC), can then be imported and leveraged within the C++/WinRT app directly.

## How many Islands? 🏝

It is up to you as a developer to decide if you'd want to leverage one larger 'Island' of space as a singular C# component for a majority of your application or sprinkle smaller individual components where they are needed. There are advantages and disadvantages for both approach.

By having a singular island you can reduce the overhead with interoperating between your C++ application and the C# components; however, this means more of your development is occuring in C# and it may be easier to consider having your whole app layer as a C# application that references a C++/WinRT Windows Runtime Component to interop with other C++ libraries or your application logic in C++.

By having multiple islands you can better encapsulate what is needed to be exposed from the C# side into the C++ app; however, you'll then have more places where you need to explicitly hook up the introp between your two layers. In the future, we hope to show how to make this easier with a potential [commanding example](https://github.com/CommunityToolkit/Sample-Windows-CppWinRT/issues/2) or how to [leverage a shared C++ component between the app and the C# Island](https://github.com/CommunityToolkit/Sample-Windows-CppWinRT/issues/1).

## Technical Challenges

The main technical challenges around this project involve the two different build systems between C++ and C# not co-operating. This is why we have to manually configure .NET Native to run from within the context of our C++ project, as well as ensure the C# dependencies are copied to our application's output folder. We've tried to comment and highlight these within the project configuration, the warnings above, and you can read more in the documentation links below.

In the future, we hope to demonstrate a [WinUI 3/Windows App SDK version of this project](https://github.com/CommunityToolkit/Sample-Windows-CppWinRT/issues/3), which may reduce some of these complexities with .NET Native as those technologies run on .NET 5+ with a separate abstraction of how the platform is integrated into the runtime environment.

## Documentation References

- https://docs.microsoft.com/windows/uwp/cpp-and-winrt-apis/use-csharp-component-from-cpp-winrt
- https://a.rcad.io/csharp-in-cppwinrt

## .NET Foundation

This project is supported by the [.NET Foundation](https://dotnetfoundation.org/) and released under the [MIT License](LICENSE.txt).
