#define NEVER_COMPILED
#ifndef NEVER_COMPILED

//path
for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations; ++simulationIndex) {
    //generate one path
    for (std::size_t timeIndex = 0; timeIndex < lastTimeIndex; ++timeIndex) {
       //simulate one step
       discretizationScheme->oneStep(randoms[simulationIndex]);
    }//output path

    //calculate Cash flow from the path.
    //if process is exp(process), calculatePV need to take exponential before using paths.
    PV += calculatePV(path);
}
//we get the all sampels of PV.


//moment match
for (std::size_t timeIndex = 0; timeIndex < lastTimeIndex; ++timeIndex) {
    //generate sample at a step.
    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations; ++simulationIndex) {
        discretizationScheme->oneStep(randoms[simulationIndex]);
    }//output all paths at the step.

    //modified moment and calculate PV until the step.
    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations; ++simulationIndex) {
        paths[simulationIndex] <- modifiedAllSamplesAtTheSteps(paths[simulationIndex], paths);
        //if caculaating exotip option, this process must be inserted
        //if process is logarithmic process, calculatePV needs to take exponential before using paths.
        PV[simulationIndex] += calculatePV(time, paths);
    }
}
//we get the all samples of PV.



#endif

