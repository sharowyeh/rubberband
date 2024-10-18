/*
 * python wrapper, NOTE: auto-generate from GPT4
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>  // For handling numpy arrays in Python
#include "RubberBandStretcher.h"

namespace py = pybind11;
using namespace RubberBand;

PYBIND11_MODULE(rubberband_wrapper, m) {
    // Bind the enum Option(from gpt, still fail for def py::init py::arg("options")
    py::enum_<RubberBandStretcher::Option>(m, "Option")
        .value("OptionProcessOffline", RubberBandStretcher::OptionProcessOffline)
        .value("OptionProcessRealTime", RubberBandStretcher::OptionProcessRealTime)
        .value("OptionStretchElastic", RubberBandStretcher::OptionStretchElastic) // obsolete
        .value("OptionStretchPrecise", RubberBandStretcher::OptionStretchPrecise) // obsolete
        .value("OptionTransientsCrisp", RubberBandStretcher::OptionTransientsCrisp)
        .value("OptionTransientsMixed", RubberBandStretcher::OptionTransientsMixed)
        // Add other enum values as needed
        .export_values();

    py::class_<RubberBandStretcher>(m, "RubberBandStretcher")
        //TODO: failed to arg() convert default argument
        .def(py::init<size_t, size_t>(), py::arg("sample_rate"), py::arg("channels"))
        // .def(py::init<size_t, size_t, RubberBandStretcher::Options, double, double>(),
        //      py::arg("sample_rate"), py::arg("channels"),
        //      py::arg("options") = RubberBandStretcher::DefaultOptions,
        //      py::arg("initial_time_ratio") = 1.0,
        //      py::arg("initial_pitch_scale") = 1.0)
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
        // TODO: fix meson cannot convert argument 2 from 'float *' to 'const float *const *
        // NOTE: the input ptr is also read as 2d array in cpp r3stretcher.cpp, gpt seems give this sample given ptr of data ptr to the native code?
        //.def("study", &RubberBandStretcher::study)
        .def("study", [](RubberBand::RubberBandStretcher &self, py::array_t<float> input, size_t samples, bool final) {
            py::buffer_info info = input.request();

            // Cast numpy data into the right format (const float *const *)
            auto data_ptr = static_cast<const float *>(info.ptr);
            const float *const data_arr[] = { data_ptr };  // Create an array of pointers

            // Call the original C++ method
            self.study(data_arr, samples, final);
        })
        //.def("process", &RubberBandStretcher::process)
        .def("process", [](RubberBand::RubberBandStretcher &self, py::array_t<float> input, size_t samples, bool final) {
            py::buffer_info info = input.request();

            auto data_ptr = static_cast<const float *>(info.ptr);
            const float *const data_arr[] = { data_ptr };

            self.process(data_arr, samples, final);
        })
        .def("available", &RubberBandStretcher::available)
        // TODO: note the given numpy 2d array format, to output buffer from stretcher to caller
        //       it may needs reserved 2d buffer with predefined channels and samples to stretcher function filled in
        //.def("retrieve", &RubberBandStretcher::retrieve)
        .def("retrieve", [](RubberBand::RubberBandStretcher &self, py::array_t<float> output, size_t samples) {
            py::buffer_info info = output.request();

            if (info.ndim != 2) {
                throw std::runtime_error("Output array must be 2D");
            }

            // Cast the NumPy array to a 2D array of float pointers
            auto data = static_cast<float *>(info.ptr);
            size_t num_channels = info.shape[0];
            size_t num_samples = info.shape[1];

            // Prepare an array of pointers, one per channel
            std::vector<float *> output_ptrs(num_channels);
            for (size_t i = 0; i < num_channels; ++i) {
                output_ptrs[i] = &data[i * num_samples];
            }

            // Call the C++ retrieve method with the array of pointers
            size_t result = self.retrieve(output_ptrs.data(), samples);
            return result;
        })
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

