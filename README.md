# ThinSaberCore

A version agnostic Beat Saber mod that can make your saber's thinner.<br>
Tested to work on any Beat Saber version above `1.27.0`.

## How to install
1. Download `ThinSaberCore.qmod` from the [latest release](https://github.com/MillzyDev/bsq-ThinSaberCore/releases/latest).
2. Install the QMOD with BMBF.
3. Done!

## How to Configure
1. Get a config file (`thinsabercore.json`)
   1. Navigate to `/sdcard/ModData/com.beatgames.beatsaber/Configs/` and save `thinsabercore.json` to your PC. <br> **or**
   2. Find a `thinsabercore.json` file that you wish to use anywhere online (as long as it is a valid config file).
2. (If you wish to change the values) Open the saved file in your favourite text editor. The file should look like the example below:
```
{
  "thickness": 0.5,
  "length": 1.0
}
```
3. Once you have finished editing the file, save it.
4. Open the BMBF Web Interface.
5. Drag the saved file into the *Upload* window.
6. Done!

## API Documentation
ThinSaberCore has an API so that mods may also set saber scales or get other information about saber scale.
This can be used to configure the Saber Scale, disable the Saber Scaling, get information about the Saber Scale, and find out whether the current Saber Scale is "legal" (may require score submission to be disabled).

There are two parts to the ThinSaberCore API: SaberScaler and SaberJudge.

### Adding to a Project
1. Open a terminal in your project's folder.
2. Run `qpm-rust dependency add thinsabercore`.
3. Run `qpm-rust restore`.
4. Done!

### SaberScaler
As the name suggests, the SaberScaler API handles scaling the sabers. To use this part of the API, include `thinsabercore/shared/API/SaberScaler.hpp`.

Most of the functions in here are self-explanatory, I will still overview them anyway.

#### Get/Set Saber Thickness
Getting and setting the saber thickness can be done using the following functions:
* Get: `ThinSaberCore::SaberScaler::getSaberThickness()` - returns a `float` value that represents the thickness of the saber. `1.0f` is the normal thickness.
* Set `ThinSaberCore::SaberScaler::setSaberThickness(float value)` - takes a `float` value as an argument that represents the thickness of the saber. `1.0f` is the normal thickness.

**NOTE:** Setting the thickness will save it to the `thinsabercore.json` config file.

#### Get/Set Saber Length
Getting and setting the saber length can be done using the following functions:
* Get: `ThinSaberCore::SaberScaler::getSaberLength()` - returns a `float` value that represents the length of the saber. `1.0f` is the normal length.
* Set: `ThinSaberCore::SaberScaler::setSaberLength(flaot value)` - takes a `float` value as an argument that represents the length of the saber. `1.0f` is the normal thickness.

**NOTE:** Setting the thickness will save it to the `thinsabercore.json` config file.

#### Getting "Legalised" Saber Thickness and Length
Legalised saber values will return the regular values, except if ThinSaberCore considers them to be "illegal", it will return the default values.

The functions are:
* `ThinSaberCore::SaberScaler::getLegalisedSaberThickness()`
* `ThinSaberCore::SaberScaler::getLegalisedSaberLength()`

respectively.

#### Getting Scales
By default, ThinSaberCore edits the scale of three objects per saber: the BasicSaber game object, which contains the saber model, and two FakeGlow objects.
The FakeGlow objects do not scale in the same way that the saber does, so it has its own scale value.

We have 2 functions for getting the Saber Scale and the Glow Scale respectively. They both return a custom `Vector3` struct, which can be found in `thinsabercore/shared/CustomTypes/Vector3.hpp`, since we do not use Codegen.

* `ThinSaberCore::SaberScaler::getSaberScale()`
* `ThinSaberCore::SaberScaler::getGlowScale()`

#### Getting Legalised Scales
Exactly the same as the previous functions, except it uses the legalised values.

They are:
* `ThinSaberCore::SaberScaler::getLegalisedSaberScale()`
* `ThinSaberCore::SaberScaler::get:LegalisedGlowScale()`

Why is it legalised and not legalized? cos i'M bRi'IsH, cAn I gEt YoU a Bo'ol o' Wo'Ah?!????!

#### Disabling the Core Scaler
You can disable the parts of ThinSaberCore that do the scaling.

* `ThinSaberCore::SaberScaler::setCoreScalerDisabled(bool value)`
* `ThinSaberCore::SaberScaler::getCoreScalerDisabled()`

### Saber Judge
This is the part that "judges" whether the current config values are "legal". To use this part of the API, include `thinsabercore/shared/API/SaberJudge.hpp`.

There are 3 functions here, they all do exactly what they sound like they do:
* `ThinSaberCore::SaberJudge::isSaberScaleLegal()` - literally just returns `isSaberThicknessLegal() && isSaberLengthLegal()`
* `ThinSaberCore::SaberJudge::isSaberThicknessLegal()`
* `ThinSaberCore::SaberJudge::isSaberLengthLegal()`