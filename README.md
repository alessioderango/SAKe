# SAKe

 <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/logoIRPI.PNG"  width="200"> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp;  <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/CNRlogo.PNG" style="float: right;" width="200"> &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;   <img src="https://github.com/alessioderango/SAKe/blob/master/README-IMG/UNICALlogo.png"  width="200"> 

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

### To know more

Terranova OG, Gariano SL, Iaquinta P, Iovine GGR. 2015. GA-SAKe: forecasting landslide
activations by a genetic-algorithms-based hydrological model. Geoscientific Model
Development 8(7), 1955–1978. [DOI: 10.5194/gmd-8-1955-2015](http://www.geosci-model-dev.net/8/1955/2015/).

### Contact Person

* Alessio De Rango - a.derango(at)unical.it 
* Giulio Iovine - giulio.iovine(at)irpi.cnr.it
