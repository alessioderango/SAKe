# SAKe
<div style="display:table-cell; vertical-align:middle">
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/logoIRPI.PNG"  width="150"> &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/CNRlogo.PNG" style="float: right;" width="150">  &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/DEMACS.png" style="margin:auto" width="200">  &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/DIAm.png"  width="200">
</div>

# Research Institute for Geo-Hydrological Protection
## in the Department of Earth System Sciences and Environmental Technology an Institute of the Italian National Research Council (CNR) and Department of Mathematic and Computer Science of University of Calabria

### Forecasting rainfall-induced landslides A new model to predict the time of occurrence of rainfallinduced
landslides, based on genetic algorithm

We developed GA-SAKe, Genetic Algorithm-based Self-Adaptive Kernel, a new model to
predict the time of occurrence of rainfall induced landslides.

GA-SAKe predicts the time of occurrence of single landslides or groups of similar landslides,
both shallow and deep-seated, using a threshold than when exceeded determines the
initiation of the landslides. The triggering threshold is defined using historical information
on rainfall and landslides.

GA-SAKe is a “black box” model based on the assumption that the stability of a slope
depends on rainfall in a linear and stationary way. Compared to other models, GA-SAKe
uses a discreet moving window (a “kernel”) and implements a “self adaptive” calibration
procedure based on “genetic algorithms”.

Exploiting the discrete kernel, GA-SAKe is flexible and suitable to simulate very complex
interactions between rainfall and slope stability. The self adaptive procedure
allows GA-SAKe to modify iteratively the shape of the kernel, based on the modelling
conditions.

Main outputs of GA-SAKe include a “mobilizing function” that allows to predict the time of
occurrence of one or more landslides, and a critical rainfall initiation threshold.

### Results

We have successfully applied GA-SAKe to predict medium-size landslides in Calabria (San
Benedetto Ullano, Acri, San Fili) and shallow landslides in the Sorrento Peninsula,
Campania.

Calibration and validation of GA-SAKe in the different study areas provided encouraging
results, that we attribute to the performance and flexibility of GA-SAKe.

The functions obtained by GA-SAKe can be integrated in early warning systems for the
possible occurrence of rainfall induced landslides.

### Installer

Please find the last version of the software SAKev0.1-beta.39 [here](https://github.com/alessioderango/SAKe/releases/download/SAKev0.1-beta.39/SAKev0.1-beta.39.exe)

### Compilation instruction

Requirements:
 - Qt 5.8 (download [here](https://download.qt.io/new_archive/qt/5.8/5.8.0/qt-opensource-windows-x86-mingw530-5.8.0.exe))
 - boost Library 1.60
 - paradisEO Library release 2.0 (download [here](https://github.com/nojhan/paradiseo/releases/tag/2.1.0-beta))

boost and paradisEO libraries already compiled for windows 7 (or higher) can be downloaded [here](https://drive.google.com/drive/folders/1t6sGG6o5hgLbKPIq-Rfxd-8HSHZEY5LY?usp=sharing).
Please before compilation move the two libraries one folder up respect to the git repo. In this way, the SAKe.pro file is ready for the compilation.

### To know more

Terranova OG, Gariano SL, Iaquinta P, Iovine GGR. 2015. GA-SAKe: forecasting landslide
activations by a genetic-algorithms-based hydrological model. Geoscientific Model
Development 8(7), 1955–1978. [DOI: 10.5194/gmd-8-1955-2015](http://www.geosci-model-dev.net/8/1955/2015/).

### Contact Person

* Alessio De Rango - a.derango(at)unical.it 
* Giulio Iovine - giulio.iovine(at)irpi.cnr.it
