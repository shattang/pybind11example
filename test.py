import model
import json

class PythonModel1(model.IModel1):
    def computemodel1(self, inputs1):
        outputs1 = []
        for input in inputs1:
            output = model.ModelOutput1()
            output.result = input.value1 + input.value2 + 0.01
            outputs1.append(output)
        return outputs1

class Model1Checker(model.IModel1):
    def __init__(self, pyModel1, cppModel1):
        model.IModel1.__init__(self)
        self.pyModel1 = pyModel1
        self.cppModel1 = cppModel1

    def computemodel1(self, inputs1):
        pyOutputs1 = self.pyModel1.computemodel1(inputs1)
        cppOutputs1 = self.cppModel1.computemodel1(inputs1)
        for i in range(len(inputs1)):
            if pyOutputs1[i].result != cppOutputs1[i].result:
                raise Exception(f"Mismatch at {i} py={pyOutputs1[i].result} cpp={cppOutputs1[i].result}")
        return cppOutputs1

class PythonModel2(model.IModel2):
    def computemodel2(self, model1, inputs2):
        outputs2 = []
        for input in inputs2:
            model1_input = model.ModelInput1()
            model1_input.value1 = input.value1
            model1_input.value2 = input.value2
            model1_outputs = model1.computemodel1([model1_input])
            output = model.ModelOutput2()
            output.result = model1_outputs[0].result * 2
            outputs2.append(output)
        return outputs2

def read_inputs_from_disk(file_path, input_class):
    with open(file_path, 'r') as file:
        data = json.load(file)
    inputs = []
    for item in data:
        input_instance = input_class()
        input_instance.value1 = item['value1']
        input_instance.value2 = item['value2']
        inputs.append(input_instance)
    return inputs

def compare_outputs(output_cpp, output_python):
    if len(output_cpp) != len(output_python):
        return False
    for o_cpp, o_py in zip(output_cpp, output_python):
        if o_cpp.result != o_py.result:
            return False
    return True

def print_model_outputs(outputs):
    for output in outputs:
        print(f'ModelOutput(result={output.result})')

def main():
    model1_cpp = model.createModel1()
    model1_python = PythonModel1()
    model2_cpp = model.createModel2()
    model2_python = PythonModel2()

    inputs1 = read_inputs_from_disk('inputs1.json', model.ModelInput1)
    inputs2 = read_inputs_from_disk('inputs2.json', model.ModelInput2)

    # Scenario 1: Using C++ Model1 and C++ Model2
    output1_cpp = model1_cpp.computemodel1(inputs1)
    output2_cpp = model2_cpp.computemodel2(model1_cpp, inputs2)
    print("Output2 from Model2 using C++ Model1 and C++ Model2:")
    print_model_outputs(output2_cpp)

    # Scenario 2: Using Python Model1 and C++ Model2
    output1_python = model1_python.computemodel1(inputs1)
    output2_python_cpp = model2_cpp.computemodel2(model1_python, inputs2)
    print("Output2 from Model2 using Python Model1 and C++ Model2:")
    print_model_outputs(output2_python_cpp)

    # Scenario 3: Using Python Model1 and Python Model2
    output2_python = model2_python.computemodel2(model1_python, inputs2)
    print("Output2 from Model2 using Python Model1 and Python Model2:")
    print_model_outputs(output2_python)

    # Compare the outputs
    if compare_outputs(output2_cpp, output2_python_cpp) and compare_outputs(output2_cpp, output2_python):
        print("The outputs from Model2 using all implementations of Model1 and Model2 match.")
    else:
        print("The outputs from Model2 using different implementations of Model1 and Model2 do not match.")

    # Can inject a dependent module checker into pipeline of any top level module
    # the checker detects differnce and immediately raises error 
    model1_checker_python = Model1Checker(model1_python, model1_cpp)
    output2_cpp_2 = model2_cpp.computemodel2(model1_checker_python, inputs2)

if __name__ == "__main__":
    main()
