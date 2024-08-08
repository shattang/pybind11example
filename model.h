#pragma once

#include <vector>

namespace Shattang
{
    namespace PybindExample
    {

        struct ModelInput1
        {
            double value1;
            double value2;
        };

        struct ModelOutput1
        {
            double result;
        };

        struct ModelInput2
        {
            double value1;
            double value2;
        };

        struct ModelOutput2
        {
            double result;
        };

        class IModel1
        {
        public:
            virtual ~IModel1() = default;
            virtual std::vector<ModelOutput1> computemodel1(const std::vector<ModelInput1> &inputs1) = 0;
        };

        class IModel2
        {
        public:
            virtual ~IModel2() = default;
            virtual std::vector<ModelOutput2> computemodel2(IModel1 *model1, const std::vector<ModelInput2> &inputs2) = 0;
        };

        IModel1 *createModel1();
        IModel2 *createModel2();

    } // namespace PybindExample
} // namespace Shattang
