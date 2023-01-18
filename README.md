# ThinSaberLite

A version agnostic[^1] Beat Saber mod that can make your saber's thinner.

[^1]: Version Agnostic: Will work on (theoretically) any Beat Saber version, even without core mods!

### Disclaimers
1. **The mod will not work if ThinSabers or ShortSaber is installed, due to conflicts.**
2. **The mod will not work if TrickSaber is installed, and `tricksaberSafeMode` is set to `true`.**
3. **The mod does not rely on any core mods to function, so there is no UI menu to edit the config. To learn about editing the config, see [Editing the Config](#editing-the-config).**

## How to Use
### Installation
1. Download the `.qmod` file from the releases page or from the [Beat Saber Modding Group](https://discord.gg/beatsabermods).
2. Install the downloaded file using [BMBF](https://bmbf.dev/). (Available in SideQuest also.)
3. Press the `Sync To BeatSaber` button.
4. Done!

### Editing the Config
ThinSaberLite does not have any form of UI. It does still have a config however!
1. Download `thinsaberlite.json` from the [releases]() page or from the [Beat Saber Modding Group](https://discord.gg/beatsabermods).
2. Open the downloaded JSON file in your favourite text editor.
3. Edit the values to your liking.
4. Save the file.
5. Select or Drag & Drop the file in [BMBF](https://bmbf.dev/).
6. Press the `Sync To BeatSaber` button.
7. Done!

## Config Values
There are two (2) editable values in the config:
- `thickness`
- `tricksaberSafeMode`

### Thickness
#### Type: Float/Real
I think this goes without saying that this is the value you edit to change the thickness. <br>
It can be any value between 0 and 1 inclusive. 1 being normal size. <br>
If you try to make this value greater than 1 or less than 0, it will default back to a thickness of 1.

### TrickSaberSafeMode
#### Type: Boolean
If this is `true`, and TrickSaber is installed, the mod will not work. <br>
This is to prevent a bug where, if the saber is thrown, the saber thrown will get thinner and longer. <br>
If you want to disable this, set the value to `false`

## Credits

* [zoller27osu](https://github.com/zoller27osu), [Sc2ad](https://github.com/Sc2ad) and [jakibaki](https://github.com/jakibaki) - [beatsaber-hook](https://github.com/sc2ad/beatsaber-hook)
* [raftario](https://github.com/raftario)
* [Lauriethefish](https://github.com/Lauriethefish), [danrouse](https://github.com/danrouse) and [Bobby Shmurner](https://github.com/BobbyShmurner) for [this template](https://github.com/Lauriethefish/quest-mod-template)
