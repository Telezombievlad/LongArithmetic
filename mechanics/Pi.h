#ifndef __PI_CALCULATIONS_H_
#define __PI_CALCULATIONS_H_

//----------------------------------------------------------------------------
//{ Includes
//----------------------------------------------------------------------------

	#include "LongArithmetic.h"

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Pi prototypes
//----------------------------------------------------------------------------

    LongNumber nilakanthaPi(LongNumber iterations);

	LongNumber circleAreaPi(LongNumber pointCount, FileWrap resources);

    LongNumber bellardPi(LongNumber iterations);

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Pi calculations
//----------------------------------------------------------------------------

	LongNumber nilakanthaPi(LongNumber iterations)
	{
		// Creating the resources to work with:

			LongNumber pi = 3_Long;
			assert(pi.ok());

			LongNumber divisor = 2_Long;
			assert(divisor.ok());

		// Main algorithm:

			for (LongNumber currentIteration = LongNumber("[0]", iterations.getRadix()); currentIteration < iterations; currentIteration++)
			{
				LongNumber previousPi = pi;
				assert(previousPi.ok());

				if (currentIteration % LongNumber("[2]", iterations.getRadix()) == LongNumber("[0]", iterations.getRadix()))
				{
					pi += 4_Long / (divisor++ * divisor++ * divisor);
				}
				else
				{
					pi -= 4_Long / (divisor++ * divisor++ * divisor);
				}

				pi.setFractionalPart(ACCURACY);

				if (previousPi == pi) break;
			}

		// Checking output:

			pi.setFractionalPart(PI_ACCURACY);
			assert(pi.ok());

		// Return statement:

			return pi;
	}

	LongNumber circleAreaPi(LongNumber pointCount, FileWrap resources)
	{
		// Checking input:

			assert(resources.ok());
			assert(pointCount.getRadix() == 10);
			assert(pointCount.ok());

		// Creating the resourses to work with:

			LongNumber radius = 10_Long;

			LongNumber pointX = LongNumber("[0].[1][7][3][8][1][8][0][2][1][2]", 10);
			LongNumber pointY = LongNumber("[6].[7][4][2][9][6][6][0][8][1][7]", 10);

			assert(radius.ok());
			assert(pointX.ok());
			assert(pointY.ok());

			LongNumber inCircle = 0_Long;
			assert(inCircle.ok());

		// Main algorithm:

			for (LongNumber currentPoint = 0_Long; currentPoint < pointCount; currentPoint++)
			{
				if (pointX.pow(2) + pointY.pow(2) < radius.pow(2)) inCircle++;

				pointX.randomize();
				pointY.randomize();
			}

		// Reading from file:

			char* resStr = resources.readFromFile();
			assert(resStr);

			LongNumber pointCountFromFile = LongNumber(resStr, 10);
			assert(pointCountFromFile.ok());

			size_t resStrIndex = 0;
			for (; resStr[resStrIndex] != '\0' && resStr[resStrIndex] != '/'; resStrIndex++)
			{
				assert(resStr[resStrIndex] != '\0');
				assert(resStr[resStrIndex] != '/');

				resStr[resStrIndex] = '_';

			}

			resStr[resStrIndex] = '_';

			LongNumber inCircleFromFile = LongNumber(resStr, 10);
			assert(inCircleFromFile.ok());

		// Working with data from file:

			pointCount += pointCountFromFile;
			inCircle += inCircleFromFile;

			LongNumber pi = 4_Long * inCircle / pointCount;
			assert(pi.ok());

		// Saving output to file:

			resources.writeToFile(pointCount.toRaw(), false);

			resources.writeToFile("/", true);

			resources.writeToFile(inCircle.toRaw(), true);

		// Checking output:

			assert(pi.ok());

		// Return statement:

			return pi;
	}

    LongNumber bellardPi(LongNumber iterations)
    {
        // Checking input:

            assert(iterations.ok());
            assert(iterations.getRadix() == 10);

        // Creating the resources to work with:

            LongNumber pi = 0_Long;
            assert(pi.ok());

            LongNumber  currentAddentum =  0_Long;
			LongNumber previousAddentum = -1_Long;
			LongNumber currentDivisor   =  1_Long;

			assert(currentAddentum .ok());
			assert(previousAddentum.ok());
			assert(currentDivisor  .ok());

        // Main algorithm:

            for (LongNumber currentIteration = 0_Long; currentIteration < iterations && currentAddentum != previousAddentum; currentIteration++)
            {
                assert(currentIteration < iterations);

				previousAddentum = currentAddentum;
				currentAddentum = 0_Long;

				currentAddentum += -( 32_Long / ( 4_Long * currentIteration + 1_Long));
				currentAddentum += -(  1_Long / ( 4_Long * currentIteration + 3_Long));
				currentAddentum +=  (256_Long / (10_Long * currentIteration + 1_Long));
				currentAddentum += -( 64_Long / (10_Long * currentIteration + 3_Long));
				currentAddentum += -(  4_Long / (10_Long * currentIteration + 5_Long));
				currentAddentum += -(  4_Long / (10_Long * currentIteration + 7_Long));
				currentAddentum +=  (  1_Long / (10_Long * currentIteration + 9_Long));

				if ((currentIteration % 2_Long) == 1_Long) currentAddentum.setNegative(!currentAddentum.isNegative());

				currentAddentum /= currentDivisor;
				currentDivisor *= 1024_Long;

				pi += currentAddentum;

				currentAddentum.setFractionalPart(ACCURACY);
				pi			   .setFractionalPart(ACCURACY);

				assert(pi.ok());
            }

			pi /= 64_Long;

		// Checking output:

			pi.setFractionalPart(PI_ACCURACY);

			assert(pi.ok());

		// Return statement:

			return pi;
    }

//}
//----------------------------------------------------------------------------

#endif
