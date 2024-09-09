/*
 * python wrapper, NOTE: auto-generate from GPT4
 *
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "RubberBandStretcher.h"

namespace py = pybind11;
using namespace RubberBand;

PYBIND11_MODULE(rubberband_wrapper, m) {
    py::class_<RubberBandStretcher>(m, "RubberBandStretcher")
        .def(py::init<size_t, size_t, RubberBandStretcher::Options, double, double>(),
             py::arg("sample_rate"), py::arg("channels"),
             py::arg("options") = RubberBandStretcher::DefaultOptions,
             py::arg("initial_time_ratio") = 1.0,
             py::arg("initial_pitch_scale") = 1.0)
        .def("reset", &RubberBandStretcher::reset)
        .def("get_engine_version", &RubberBandStretcher::getEngineVersion)
        .def("set_time_ratio", &RubberBandStretcher::setTimeRatio)
        .def("set_pitch_scale", &RubberBandStretcher::setPitchScale)
        .def("set_formant_scale", &RubberBandStretcher::setFormantScale)
        .def("get_time_ratio", &RubberBandStretcher::getTimeRatio)
        .def("get_pitch_scale", &RubberBandStretcher::getPitchScale)
        .def("get_formant_scale", &RubberBandStretcher::getFormantScale)
        .def("get_preferred_start_pad", &RubberBandStretcher::getPreferredStartPad)
        .def("get_start_delay", &RubberBandStretcher::getStartDelay)
        .def("get_latency", &RubberBandStretcher::getLatency)
        .def("get_channel_count", &RubberBandStretcher::getChannelCount)
        .def("set_transients_option", &RubberBandStretcher::setTransientsOption)
        .def("set_detector_option", &RubberBandStretcher::setDetectorOption)
        .def("set_phase_option", &RubberBandStretcher::setPhaseOption)
        .def("set_formant_option", &RubberBandStretcher::setFormantOption)
        .def("set_pitch_option", &RubberBandStretcher::setPitchOption)
        .def("set_expected_input_duration", &RubberBandStretcher::setExpectedInputDuration)
        .def("set_max_process_size", &RubberBandStretcher::setMaxProcessSize)
        .def("get_process_size_limit", &RubberBandStretcher::getProcessSizeLimit)
        .def("get_samples_required", &RubberBandStretcher::getSamplesRequired)
        .def("set_key_frame_map", &RubberBandStretcher::setKeyFrameMap)
        .def("study", &RubberBandStretcher::study)
        .def("process", &RubberBandStretcher::process)
        .def("available", &RubberBandStretcher::available)
        .def("retrieve", &RubberBandStretcher::retrieve)
        .def("get_frequency_cutoff", &RubberBandStretcher::getFrequencyCutoff)
        .def("set_frequency_cutoff", &RubberBandStretcher::setFrequencyCutoff)
        .def("get_input_increment", &RubberBandStretcher::getInputIncrement)
        .def("get_output_increments", &RubberBandStretcher::getOutputIncrements)
        .def("get_phase_reset_curve", &RubberBandStretcher::getPhaseResetCurve)
        .def("get_exact_time_points", &RubberBandStretcher::getExactTimePoints)
        .def("calculate_stretch", &RubberBandStretcher::calculateStretch)
        .def("set_debug_level", &RubberBandStretcher::setDebugLevel)
        .def_static("set_default_debug_level", &RubberBandStretcher::setDefaultDebugLevel)
        .def("get_library_version", &RubberBandStretcher::getLibraryVersion);
}

