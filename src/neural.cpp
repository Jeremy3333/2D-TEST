#include "Neural.hpp"
#include "Utils.hpp"
#include <random>
#include <iostream>

float Sigmoid(float x)
{
    return x;
}

float ReLU(float x)
{
    return x > 0 ? x : 0;
}
Neural::Neural()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            HiddenLayerBias[i][j] = ((rand() % 20) - 10.0f);
        }
    }
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            HiddenLayerResult[i][j] = 0;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            WeightsIL_HL1[i][j] = ((rand() % 200) - 100.0f) / 100.0f;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            WeightsHL1_HL2[i][j] = ((rand() % 200) - 100.0f) / 100.0f;
        }
    }
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            WeightsHL2_OL[i][j] = ((rand() % 200) - 100.0f) / 100.0f;
        }
    }
}

Neural::Neural(const Neural &Heredity)
{
    //Copy Heredity with some mutations
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            HiddenLayerBias[i][j] = Heredity.HiddenLayerBias[i][j];
            if(rand() % 100 < BRAIN_MUTATION_CHANCE)
            {
                HiddenLayerBias[i][j] += ((rand() % 20) - 10.0f);
                if(HiddenLayerBias[i][j] > 10.0f)
                    HiddenLayerBias[i][j] = 10.0f;
                else if(HiddenLayerBias[i][j] < -10.0f)
                    HiddenLayerBias[i][j] = -10.0f;
            }
        }
    }
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            HiddenLayerResult[i][j] = Heredity.HiddenLayerResult[i][j];
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            WeightsIL_HL1[i][j] = Heredity.WeightsIL_HL1[i][j];
            if(rand() % 100 < BRAIN_MUTATION_CHANCE)
            {
                WeightsIL_HL1[i][j] += ((rand() % 200) - 100.0f) / 100.0f;
                if(WeightsIL_HL1[i][j] > 1.0f)
                    WeightsIL_HL1[i][j] = 1.0f;
                else if(WeightsIL_HL1[i][j] < -1.0f)
                    WeightsIL_HL1[i][j] = -1.0f;
            }
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            WeightsHL1_HL2[i][j] = Heredity.WeightsHL1_HL2[i][j];
            if(rand() % 100 < BRAIN_MUTATION_CHANCE)
            {
                WeightsHL1_HL2[i][j] += ((rand() % 200) - 100.0f) / 100.0f;
                if(WeightsHL1_HL2[i][j] > 1.0f)
                    WeightsHL1_HL2[i][j] = 1.0f;
                else if(WeightsHL1_HL2[i][j] < -1.0f)
                    WeightsHL1_HL2[i][j] = -1.0f;
            }
        }
    }
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            WeightsHL2_OL[i][j] = Heredity.WeightsHL2_OL[i][j];
            if(rand() % 100 < BRAIN_MUTATION_CHANCE)
            {
                WeightsHL2_OL[i][j] += ((rand() % 200) - 100.0f) / 100.0f;
                if(WeightsHL2_OL[i][j] > 1.0f)
                    WeightsHL2_OL[i][j] = 1.0f;
                else if(WeightsHL2_OL[i][j] < -1.0f)
                    WeightsHL2_OL[i][j] = -1.0f;
            }
        }
    }
}

Neural::~Neural() {}

void Neural::Solve(float Input[2], float Output[2])
{
    for(int i = 0; i < 4; i++)// result of HiddenLayer 1
    {
        HiddenLayerResult[0][i] = 0;
        for(int j = 0; j < 2; j++)
        {
            HiddenLayerResult[0][i] += Input[j] * WeightsIL_HL1[i][j];
        }
        HiddenLayerResult[0][i] += HiddenLayerBias[0][i];
        HiddenLayerResult[0][i] = ReLU(HiddenLayerResult[0][i]);
    }
    for(int i = 0; i < 4; i++)// result of HiddenLayer 2
    {
        HiddenLayerResult[1][i] = 0;
        for(int j = 0; j < 4; j++)
        {
            HiddenLayerResult[1][i] += HiddenLayerResult[0][j] * WeightsHL1_HL2[i][j];
        }
        HiddenLayerResult[1][i] += HiddenLayerBias[1][i];
        HiddenLayerResult[1][i] = ReLU(HiddenLayerResult[1][i]);
    }
    for(int i = 0; i < 2; i++)// result of OutputLayer
    {
        Output[i] = 0;
        for(int j = 0; j < 4; j++)
        {
            Output[i] += HiddenLayerResult[1][j] * WeightsHL2_OL[i][j];
        }
        Output[i] = Output[i];
    }
}