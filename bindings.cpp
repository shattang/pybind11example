#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "model.h"

namespace py = pybind11;
using namespace Shattang::PybindExample;

class PyIModel1 : public IModel1
{
public:
    using IModel1::IModel1;

    std::vector<ModelOutput1> computemodel1(const std::vector<ModelInput1> &inputs1) override
    {
        PYBIND11_OVERRIDE_PURE(
            std::vector<ModelOutput1>, // Return type
            IModel1,                   // Parent class
            computemodel1,             // Name of function in C++ (must match Python name)
            inputs1                    // Argument(s)
        );
    }
};

class PyIModel2 : public IModel2
{
public:
    using IModel2::IModel2;

    std::vector<ModelOutput2> computemodel2(IModel1 *model1, const std::vector<ModelInput2> &inputs2) override
    {
        PYBIND11_OVERRIDE_PURE(
            std::vector<ModelOutput2>, // Return type
            IModel2,                   // Parent class
            computemodel2,             // Name of function in C++ (must match Python name)
            model1,                    // Argument(s)
            inputs2);
    }
};

PYBIND11_MODULE(model, m)
{
    py::class_<ModelInput1>(m, "ModelInput1")
        .def(py::init<>())
        .def_readwrite("value1", &ModelInput1::value1)
        .def_readwrite("value2", &ModelInput1::value2);

    py::class_<ModelOutput1>(m, "ModelOutput1")
        .def(py::init<>())
        .def_readwrite("result", &ModelOutput1::result);

    py::class_<ModelInput2>(m, "ModelInput2")
        .def(py::init<>())
        .def_readwrite("value1", &ModelInput2::value1)
        .def_readwrite("value2", &ModelInput2::value2);

    py::class_<ModelOutput2>(m, "ModelOutput2")
        .def(py::init<>())
        .def_readwrite("result", &ModelOutput2::result);

    py::class_<IModel1, PyIModel1>(m, "IModel1")
        .def(py::init<>())
        .def("computemodel1", &IModel1::computemodel1);

    py::class_<IModel2, PyIModel2>(m, "IModel2")
        .def(py::init<>())
        .def("computemodel2", &IModel2::computemodel2);

    m.def("createModel1", &createModel1, py::return_value_policy::reference);
    m.def("createModel2", &createModel2, py::return_value_policy::reference);
}
