# GA SAKe 2.0
## An advanced hydrological model to predict the activation of landslides

<div style="display:table-cell; vertical-align:middle">
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/logo-irpi-cnr.png"  width="250"> &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/DEMACS.png" style="margin:auto" width="250">  &nbsp; &nbsp; &nbsp;
 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/DIAm.png"  width="250">
</div>

<img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/SAKe.png" >
<img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/SAKe-val_v2.png" >
<img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/SAKe-regr.png" >


GA SAKe is a black-box model assuming that slope stability depends on rainfall in a linear, steady-state manner. It employs Genetic Algorithms to predict the timing of triggering of landslides, based on rainfall series and previous activations. Calibration provides families of optimal, discretized kernels that maximize the fitness. For each kernel, a mobility function can be obtained through convolution with the rain series. Once validated, the model can be applied to estimate future activations.
This new release (2.0) includes improvements concerning software optimization, graphical user interface, input format, selection criteria, and fitness types. A specific regression tool allows to obtain suitable analytical expressions to approximate a given kernel, for a better understanding of groundwater dynamics.
GA SAKe-2.0 could be integrated within an early-warning system to estimate the triggering of landslides, based on measured/forecasted rainfall. 

 - The instruction guide can be found [here](https://github.com/alessioderango/SAKe/blob/master/guide_and_example/Appendix%20A%20-%20Instruction%20Guide.pdf).
 - An example of an application, including calibration, validation and regression, to the Uncino landslide case study is available [here](https://github.com/alessioderango/SAKe/blob/master/guide_and_example/Appendix%20B%20-%20An%20example%20of%20application.pdf).
 - Data concerning an application to the Uncino landslide in Southern Italy, characterized by 6 re-activations, can be found [here](https://github.com/alessioderango/SAKe/tree/master/case_study). 

### Installer for Windows 7 (or higher)

Please find the last version of the software SAKev0.1-beta.39 [here](https://github.com/alessioderango/SAKe/releases/download/SAKev0.1-beta.39/SAKev0.1-beta.39.exe)

### Compilation instruction

GA SAKe can be compiled both for Windows and Linux.


Requirements:
 - Qt 5.8 ([Windows installer](https://download.qt.io/new_archive/qt/5.8/5.8.0/qt-opensource-windows-x86-mingw530-5.8.0.exe), [Linux installer](https://download.qt.io/new_archive/qt/5.8/5.8.0/qt-opensource-linux-x64-5.8.0.run))
 - boost Library 1.60 ([Windows sources](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.zip), [Linux sources](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz))
 - paradisEO Library release 2.0 ([Windowd/Linux sources](https://github.com/nojhan/paradiseo/releases/tag/2.1.0-beta))

Both the boost and paradisEO binaries for Windows 7 (or higher) can be downloaded from [here](https://drive.google.com/drive/folders/1t6sGG6o5hgLbKPIq-Rfxd-8HSHZEY5LY?usp=sharing).
Before compiling, please move the two libraries one folder up with respect to the git repo folder. If you prefer another location, please update the paths in the SAKe.pro project file.

### To know more
If you find GA SAKe useful for your research or work, you may consider citing the following papers in your scientific publications or technical reports:

De Rango A, Terranova A, D'Ambrosio D, Lupiano V, Mendicino G, Terranova OG, Iovine G, submitted.
GA SAKe-2.0 – An advanced hydrological model to predict the activation of landslides. Computers & Geosciences.

Terranova O., Gariano S.L., Iaquinta P., Lupiano V., Rago V., Iovine G., 2018. Examples of application of GASAKe 
for predicting the occurrence of rainfall-induced landslides in southern Italy. Geosciences (Switzerland), 8 (2), art. no. 78. 
[DOI: 10.3390/geosciences8020078](https://doi.org/10.3390/geosciences8020078)

Terranova OG, Gariano SL, Iaquinta P, Iovine GGR. 2015. GA SAKe: forecasting landslide
activations by a genetic-algorithms-based hydrological model. Geoscientific Model
Development 8(7), 1955–1978. [DOI: 10.5194/gmd-8-1955-2015](http://www.geosci-model-dev.net/8/1955/2015/).

### Contact Person

* Giulio Iovine - giulio.iovine(at)cnr.it
* Alessio De Rango - a.derango(at)unical.it

### License
This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/agpl-3.0.en.html.
