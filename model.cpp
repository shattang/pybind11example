#include "model.h"

namespace Shattang
{
    namespace PybindExample
    {

        class Model1 : public IModel1
        {
        public:
            std::vector<ModelOutput1> computemodel1(const std::vector<ModelInput1> &inputs1) override
            {
                std::vector<ModelOutput1> outputs;
                for (const auto &input : inputs1)
                {
                    ModelOutput1 output;
                    output.result = input.value1 + input.value2; // Dummy calculation
                    outputs.push_back(output);
                }
                return outputs;
            }
        };

        class Model2 : public IModel2
        {
        public:
            std::vector<ModelOutput2> computemodel2(IModel1 *model1, const std::vector<ModelInput2> &inputs2) override
            {
                std::vector<ModelOutput2> outputs;
                for (const auto &input : inputs2)
                {
                    ModelInput1 model1_input{input.value1, input.value2};
                    auto model1_outputs = model1->computemodel1({model1_input});
                    ModelOutput2 output;
                    output.result = model1_outputs[0].result * 2; // Dummy calculation
                    outputs.push_back(output);
                }
                return outputs;
            }
        };

        IModel1 *createModel1()
        {
            return new Model1();
        }

        IModel2 *createModel2()
        {
            return new Model2();
        }

    } // namespace PybindExample
} // namespace Shattang
