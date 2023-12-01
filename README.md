# lytroIO 

> [!IMPORTANT]
> This repo is still under development.

> lytroIO aims to be a small C++ library to process Lytro files (extracting metadatas, saving images,... )


- **Source code** 📁: [github.com/mtouzot/lytroIO](https://github.com/mtouzot/lytroIO)
- **Issues** 🆘: [github.com/mtouzot/lytroIO/issues](https://github.com/mtouzot/lytroIO/issues)

# Description

Before being acquired and closed by Google in 2018, Lytro was an company developing [plenoptic cameras](https://en.wikipedia.org/w/index.php?title=Light_field_camera) for the general public.

The main use of light-field camera is the ability to change image focus during post-processing and thus, for example, being able to remove any blur or to create animated GIF with just one button pressed on the DSLR.

<p align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/e/eb/Lytro_Illum_light_field_camera_demonstration.jpg" align="center">

Image taken with a Lytro Illum by Doodybutch, published under [CC BY-SA 4.0 license](https://creativecommons.org/licenses/by-sa/4.0/deed.en)

<p align="center">
<img src="https://raw.githubusercontent.com/hahnec/color-matcher/master/tests/data/view_animation_7px.gif" align="center">

Image taken with a Lytro camera animated by [Christopher Hahne](http://www.christopherhahne.de/), published under [GNU General Public License version 3 license](https://opensource.org/license/gpl-3-0) for his [PlenoptiCam](https://github.com/hahnec/plenopticam) software.

# Compilation

Here are the commands to compile this project :
```console
cd <lytroio_build_directory>
cmake -G <cmake_generator> -DBUILD_EXAMPLES=<ON/OFF> -DBUILD_DOCS=<ON/OFF> <lytroio_source_directory>
cmake --build . --config <cfg>
```
By default, **BUILD_EXAMPLES** and **BUILD_DOCS** are set to **OFF**.

# External ressources

Here is some further reading or other projects : 
* [lfptools](https://github.com/nrpatel/lfptools) : a C tool to split Lytro files
* [Lyli](https://github.com/martin-pr/lyli) : the open-source alternative to the Lytro Desktop application
* [Plenoptic](http://www.plenoptic.info/) : a website by Christopher Hahne, gather infos about Standard Plenoptic Camera
* [Lytro Power Tools](https://github.com/rgon/lytro-power-tools) : a bunch of ressources linked to Lytro cameras and files