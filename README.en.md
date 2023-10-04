# KHistory
🔥KHistory is an elegant & cross-platform keyboard/gamepad key detection and history display tool, no need to install, just run the single executable file (about 900kb in size).

[**中文**](README.md)


### No installation, single-file download and use

> **Click [Release](https://github.com/Sunrisepeak/KHistory/releases) to get the latest version for your platform**

![KHistory Demo](docs/imgs/khistory.demo.png)

## I. Features

- Keyboard key detection
- Gamepad key detection
- Controls
  - Key history record count
  - Transparency
  - Detection frame rate
  - Visual plugin selection
- Key visualization and customization (custom key layout/remap key names/customize key highlight colors/other)

## II. Platform Support

|      Feature\Platform     |  Linux   | Windows  | MacOS |  Remarks  |
| :-----------------------: | :------: | :------: | :---: | :-------: |
|   Keyboard key detection  | &#x2705; | &#x2705; |       |           |
|   Gamepad key detection   |          | &#x2705; |       |           |
|   Control - Key history record count   | &#x2705; | &#x2705; |       |           |
|   Control - Transparency  | &#x2705; | &#x2705; |       |           |
|   Control - Detection frame rate | &#x2705; | &#x2705; |       |           |
|   Key visualization | &#x2705; | &#x2705; |       | Supported plugin extension/customization |
|   Plugin extension   | &#x2705; | &#x2705; | &#x2705; |           |

**Note: MacOS support coming soon**

## III. Possible Use Cases

- Educational tutorials
- Live streaming
- Video production
- Personal operation analysis
- Other scenarios that require displaying key input records

## IV. Demonstrations

### Keyboard key detection
![Keyboard Demo](docs/imgs/khistory-keyboard.demo.gif)

### Gamepad key detection
![Gamepad Demo](docs/imgs/khistory-gamepad.demo.gif)

## V. Plugin Module / Custom Plugins
> **Developers:** You can develop or extend plugins according to your needs to create custom key visualization panels.
>
> **Users:** You can choose the appropriate plugins for your use case, such as keyboard or gamepad visualization, as shown below:

![Plugin Control](docs/imgs/plugin-control.png)

### Plugin Module Features
- Basic plugin functionality - Users can freely switch plugins for key visualization based on their scenario (e.g., keyboard, gamepad, etc.).
- Mini plugin framework PluginBase - Provides standard interfaces and automatically handles key events and layout (key state) updates in the background.
- Automatic plugin registration - Place the plugin in the `kplugin/auto-register` directory to automatically register it during compilation.
- Basic plugins and plugin extensions - Basic keyboard and gamepad plugins are provided, and users can develop their own plugins without needing to understand C++/ImGui.
  - Custom key layout
  - Remap key names
  - Customize key highlight colors
  - Others

### Plugin Examples / Basic Plugins

#### [Plugin Base - Keyboard](Keyboard.kplugin.hpp) - Basic keyboard plugin
![Keyboard Plugin](docs/imgs/Keyboard.kplugin.png)

#### [Plugin Base - Gamepad](kplugin/Gamepad.kplugin.hpp) - Basic gamepad plugin
![Gamepad Plugin](docs/imgs/Gamepad.kplugin.png)

### Plugin Development / Customization Process - No need to understand C++/ImGui

**Note: For plugin details and development, please refer to the [Plugin Documentation](kplugin).**

## VI. Contributions and Interesting Plugins

> Feel free to share interesting plugins in this discussion - [KPlugin - Interesting Plugins Discussion](https://github.com/Sunrisepeak/KHistory/discussions/9)

![Plugin Set](docs/imgs/kplugin.set.png)

## VII. Related Videos

> **More introductions/development updates -〉[Link](https://space.bilibili.com/65858958/channel/seriesdetail?sid=3473247)**

- [Open Source Software: KHistory Key Detection and History Display Tool Introduction](https://www.bilibili.com/video/BV1Xx4y1o7cp)
- [KHistory: Street Fighter 6 "Highlight" Actions Using C](https://www.bilibili.com/video/BV1W14y1X7vD)
- [Open Source Software: KHistory Plugin Module Basic Features and Extensions](https://www.bilibili.com/video/BV1Uk4y1g7aU)

## VIII. Related Links

- [**KHistory**](https://github.com/Sunrisepeak/KHistory)
- [**DSVisual**](https://github.com/Sunrisepeak/DSVisual)
- [**DStruct**](https://github.com/Sunrisepeak/DStruct)
- [**imgui**](https://github.com/ocornut/imgui)
- [**xmake**](https://github.com/xmake-io/xmake)