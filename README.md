# SAKe
<div style="display:table-cell; vertical-align:middle">
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/logo-irpi-cnr.png"  width="250"> &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/DEMACS.png" style="margin:auto" width="250">  &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/DIAm.png"  width="250">
</div>

### Forecasting rainfall-induced landslides: A model to predict the time of occurrence of rainfall-induced landslides based on a genetic algorithm

<img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/SAKe.png" >
<img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/SAKe-regr.png" >

We developed GA-SAKe, Genetic Algorithm-based Self-Adaptive Kernel, a new model to
predict the time of occurrence of rainfall-induced landslides.

GA-SAKe predicts the time of occurrence of single landslides or groups of similar landslides,
both shallow and deep-seated, using a threshold that when exceeded, determines the
initiation of the landslides. The triggering threshold is defined using historical information
on rainfall and landslides.

GA-SAKe is a "black box" model based on the assumption that the stability of a slope
depends on rainfall in a linear and stationary way. Compared to other models, GA-SAKe
uses a discreet moving window (a "kernel") and implements a "self-adaptive" calibration
procedure based on "genetic algorithms".

Exploiting the discrete kernel, GA-SAKe is flexible and suitable to simulate very complex
interactions between rainfall and slope stability. The self-adaptive procedure
allows GA-SAKe to modify iteratively the shape of the kernel based on the modelling
conditions.

The main outputs of GA-SAKe include a "mobilizing function" that allows predicting the time of
occurrence of one or more landslides, and a critical rainfall initiation threshold.

### Results

We have successfully applied GA-SAKe to predict medium-size landslides in Calabria (San
Benedetto Ullano, Acri, San Fili) and shallow landslides in the Sorrento Peninsula,
Campania, Italy.

Calibration and validation of GA-SAKe in the different study areas provided encouraging
results that we attribute to the performance and flexibility of GA-SAKe.

The functions obtained by GA-SAKe can be integrated into early warning systems for the
possible occurrence of rainfall-induced landslides.

### Installer for Windows 7 (or higher)

Please find the last version of the software SAKev0.1-beta.39 [here](https://github.com/alessioderango/SAKe/releases/download/SAKev0.1-beta.39/SAKev0.1-beta.39.exe)

### Compilation instruction

GA-SAKe can be compiled both for Windows and Linux.


Requirements:
 - Qt 5.8 ([Windows installer](https://download.qt.io/new_archive/qt/5.8/5.8.0/qt-opensource-windows-x86-mingw530-5.8.0.exe), [Linux installer](https://download.qt.io/new_archive/qt/5.8/5.8.0/qt-opensource-linux-x64-5.8.0.run))
 - boost Library 1.60 ([Windows sources](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.zip), [Linux sources](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz))
 - paradisEO Library release 2.0 ([Windowd/Linux sources](https://github.com/nojhan/paradiseo/releases/tag/2.1.0-beta))

Both the boost and paradisEO binaries for Windows 7 (or higher) can be downloaded from [here](https://drive.google.com/drive/folders/1t6sGG6o5hgLbKPIq-Rfxd-8HSHZEY5LY?usp=sharing).
Before compiling, please move the two libraries one folder up with respect to the git repo folder. If you prefer another location, please update the paths in the SAKe.pro project file.

### To know more

Terranova OG, Gariano SL, Iaquinta P, Iovine GGR. 2015. GA-SAKe: forecasting landslide
activations by a genetic-algorithms-based hydrological model. Geoscientific Model
Development 8(7), 1955–1978. [DOI: 10.5194/gmd-8-1955-2015](http://www.geosci-model-dev.net/8/1955/2015/).

### Contact Person

* Giulio Iovine - giulio.iovine(at)irpi.cnr.it
* Alessio De Rango - a.derango(at)unical.it

### License
This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/agpl-3.0.en.html.
