#ifndef __LONG_ARITHMETICS_H__
#define __LONG_ARITHMETICS_H__

//----------------------------------------------------------------------------
//{ Includes
//----------------------------------------------------------------------------

	#include "TXLib.h"
	#include "Debugging.h"
	#include "FileWrap.h"

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Constants
//----------------------------------------------------------------------------

    // Char constants:

        const char
        NUMBER_BASE       = '0', NUMBER_END       = '9',
        BIG_LETTER_BASE   = 'A', BIG_LETTER_END   = 'Z',
        SMALL_LETTER_BASE = 'a', SMALL_LETTER_END = 'z';

    // Algorithmic:

        const size_t ACCURACY = 16;
		const size_t PI_ACCURACY = ACCURACY;

    // Other:

        const size_t MAX_ARRAY_SIZE = 100000;

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Prototypes
//----------------------------------------------------------------------------

    // Additional functions:

        char* intToStr(unsigned int integer);

        //----------------------------------------------------------------------------

        unsigned int ML_atoi(char* number, unsigned int radix);
        char*        ML_itoa(int   number, unsigned int radix);

        unsigned int maximum(unsigned int numberA, unsigned int numberB);
        unsigned int minimum(unsigned int numberA, unsigned int numberB);

        int  ML_strLen (const char* myString);
        void reverseStr(char* myString);

        char          toUpper(char charecter);
        unsigned int  charToInt(char charecter);
        char          intToChar(unsigned int integer);

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Class LongNumber
//----------------------------------------------------------------------------

    class LongNumber
    {
        public:
            // Constructors & destructor:

                LongNumber(const char numberString[], unsigned int radix);

                LongNumber(long long int number, unsigned int radix);

                LongNumber(const LongNumber& number);

                ~LongNumber();

            // Getters && setters:

                unsigned int getDigit(size_t digitIndex) const;
                LongNumber&  setDigit(size_t digitIndex, unsigned int digit);

                size_t      getSize() const;
                LongNumber& setSize(size_t newSize);

                unsigned int getRadix() const;
                LongNumber&  setRadix(unsigned int newRadix);

                bool         isNegative() const;
                LongNumber& setNegative(bool negative = true);

                size_t      getDecimalPoint() const;
                LongNumber& setDecimalPoint(size_t decimalPoint);

                size_t      getIntegerPart() const;
                LongNumber& setIntegerPart(size_t newIntegerPart);

				size_t		getFractionalPart() const;
				LongNumber& setFractionalPart(size_t newFractionalPart);

            // Functionas:

                // User functions:

					// Verification:

						bool ok() const;

						void print() const;

						char* toRaw() const;

						char* toUserRaw() const;

					// Other:

						LongNumber& shift(int numberShift);

						LongNumber& normalize();

						LongNumber& randomize();

						LongNumber& adapt(const LongNumber& number);

						LongNumber& setBothInteger(LongNumber* number);

                // Addition && substraction::

                    LongNumber sum(const LongNumber& number) const;

                    void inverseAndAdd();

                // Multiplication:

                    LongNumber product(const LongNumber& number) const;

                    void multiplyByDigit(unsigned int factor);

                // Division:

                    LongNumber divideWithRemainder(const LongNumber& number) const;

                    LongNumber divide(const LongNumber& number) const;

                    unsigned int divideDigit(size_t currentDigit, const LongNumber& number);

                    size_t searchForDivisor(const LongNumber& number) const;

				// Factorial:

					LongNumber factorial() const;

				// Power:

					LongNumber pow(const int power) const;

				// Root:

					LongNumber root(const unsigned int base) const;

            // Operators:

                // Assignment:

					// Bitwise arithmetics:

						LongNumber& operator>>=(const unsigned int numberShift);
						LongNumber& operator<<=(const unsigned int numberShift);

						LongNumber& operator&=(const LongNumber& number);
						LongNumber& operator|=(const LongNumber& number);
						LongNumber& operator^=(const LongNumber& number);

					// Regular arithmetics:

						LongNumber& operator=(const LongNumber& number);

						LongNumber& operator+=(const LongNumber& number);
						LongNumber& operator-=(const LongNumber& number);
						LongNumber& operator*=(const LongNumber& number);
						LongNumber& operator/=(const LongNumber& number);
						LongNumber& operator%=(const LongNumber& number);

                // Increment/decrement:

                    // Prefix:

                        LongNumber& operator++();
                        LongNumber& operator--();

                    // Postfix:

                        LongNumber operator++(int);
                        LongNumber operator--(int);

                // Arithmetic:

					// Bitwise arithmetics:

						LongNumber operator~() const;

						LongNumber operator>>(const unsigned int numberShift) const;
						LongNumber operator<<(const unsigned int numberShift) const;

						LongNumber operator&(const LongNumber& number) const;
						LongNumber operator|(const LongNumber& number) const;
						LongNumber operator^(const LongNumber& number) const;

					// Regular arithmetics:

						LongNumber operator+() const;
						LongNumber operator-() const;

						LongNumber operator+(const LongNumber& number) const;
						LongNumber operator-(const LongNumber& number) const;
						LongNumber operator*(const LongNumber& number) const;
						LongNumber operator/(const LongNumber& number) const;
						LongNumber operator%(const LongNumber& number) const;

                // Comparison:

                    bool operator==(const LongNumber& number) const;
                    bool operator< (const LongNumber& number) const;
                    bool operator!=(const LongNumber& number) const;
                    bool operator> (const LongNumber& number) const;
                    bool operator<=(const LongNumber& number) const;
                    bool operator>=(const LongNumber& number) const;

				// Logical:

					bool operator!() const;
					bool operator&&(const LongNumber& number) const;
					bool operator||(const LongNumber& number) const;

					bool operator&&(const bool statement) const;
					bool operator||(const bool statement) const;

				// Access:

					unsigned int operator[](const size_t digitIndex) const;

                // User-defined litearls:

                    friend LongNumber operator"" _Long(const unsigned long long int number);
                    friend LongNumber operator"" _Long(const char* number);

        private:
            unsigned int* number_;
            unsigned int  size_;

            unsigned int radix_;

            bool negative_;

            size_t decimalPoint_;
    };


    //----------------------------------------------------------------------------
    //{ Constructors && destructor
    //----------------------------------------------------------------------------

		LongNumber::LongNumber(const char numberString[], unsigned int radix) :
			number_       (NULL),
			size_         (0),
			radix_        (radix),
			negative_     (false),
			decimalPoint_ (0)

		{
			// Checking input:

				assert(numberString && numberString[0]);

			// Creating the resources to work with:

				size_ = ML_strLen(numberString);

				unsigned int* newNumber = (unsigned int*) calloc(size_, sizeof(*newNumber));
				assert(newNumber);

			// Main algorithm:

				// Translating numberString into flipped array of remainders:

                    size_t digit = 0;

                    for (size_t numberStringIndex = 0; numberString[numberStringIndex] != '\0' && numberString[numberStringIndex] != '/'; numberStringIndex++)
                    {
                        assert(numberString[numberStringIndex] != '\0');
                        assert(numberString[numberStringIndex] != '/');

                        if (numberString[numberStringIndex] == '-') negative_ = true;
                        if (numberString[numberStringIndex] == '.') decimalPoint_ = digit;

                        if (numberString[numberStringIndex] == '[')
                        {
                            numberStringIndex++;

                            size_t currentDigitSize = 10;

                            char currentDigit[10];
                            for (size_t index = 0; index < currentDigitSize; index++)
                            {
                                assert(index < currentDigitSize && currentDigitSize < MAX_ARRAY_SIZE);

                                currentDigit[index] = 0;
                            }


                            for (size_t currentDigitIndex = 0;
                                 currentDigitIndex < currentDigitSize    &&
                                 numberString[numberStringIndex] != '\0' &&
                                 numberString[numberStringIndex] != '/'  &&
                                 numberString[numberStringIndex] != ']';
                                 numberStringIndex++)
                            {
                                assert(currentDigitIndex < currentDigitSize && currentDigitSize < MAX_ARRAY_SIZE);
                                assert(numberString[numberStringIndex] != '\0');
                                assert(numberString[numberStringIndex] != '/');
                                assert(numberString[numberStringIndex] != ']');

                                if (NUMBER_BASE <= numberString[numberStringIndex] && numberString[numberStringIndex] <= NUMBER_END)
                                {
                                    currentDigit[currentDigitIndex] = numberString[numberStringIndex];
                                    currentDigitIndex++;
                                }
                            }

                                newNumber[digit] = ML_atoi(currentDigit, 10);

                                digit++;
                        }
                    }

				// Translating flipped remainder array into normal remainder array:

                    size_ = digit;

                    if (decimalPoint_ != 0) decimalPoint_ = size_ - decimalPoint_;

                    number_ = (unsigned int*) calloc(size_, sizeof(*number_));
                    assert(number_);

                    for (size_t i = 0; i < size_; i++)
                    {
                        assert(i < size_);

                        number_[i] = newNumber[size_ - i - 1];
                    }

                    free(newNumber);

			// Checking && fixing output:

				assert(ok());

				normalize();
		}

        LongNumber::LongNumber(long long int number, unsigned int radix) :
            number_      (NULL),
			size_        (0),
			radix_       (radix),
			negative_    (false),
			decimalPoint_(0)
        {
            // Checking input:

                assert(1 < radix_);

            // Creating the resources to work with:

                // Setting negativeness:

                    if (number < 0)
                    {
                        negative_ = true;
                        number *= -1;
                    }

                // Setting size && creating number array:

					if (number == 0) size_ = 1;
					else size_ = ROUND(log(static_cast<double>(number))/log(static_cast<double>(radix))) + 1;

                    number_ = (unsigned int*) calloc(size_, sizeof(*number_));

					assert(number_);

            // Main algorithm:

                for (size_t digit = 0; digit < size_ && number != 0; digit++)
                {
                    assert(digit < size_);
                    assert(size_ < MAX_ARRAY_SIZE);

                    number_[digit] = static_cast<unsigned int>((number % radix_));
                    number /= radix_;
                }

            // Checking && fixing output:

                assert(ok());

                normalize();
        }

        LongNumber::LongNumber(const LongNumber& number) :
            number_       (NULL),
            size_         (0),
            radix_        (0),
            negative_     (false),
            decimalPoint_ (0)
        {
            // Checking input:

                assert(number.ok());

            // Setting everything:

                size_ = number.getSize();

                radix_ = number.getRadix();

                negative_ = number.isNegative();

                decimalPoint_ = number.getDecimalPoint();

                number_ = (unsigned int*) calloc(size_, sizeof(*number_));
                assert(number_);

                for (size_t digit = 0; digit < size_; digit++)
                {
                    assert(digit < size_);
                    assert(size_ < MAX_ARRAY_SIZE);

                    number_[digit] = number.getDigit(digit);
                }

            // Checking output:

                assert(ok());
                assert(number.ok());
        }

        LongNumber::~LongNumber()
        {
            free(number_);
        }

    //}
    //----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
    //{ Getters & setters
    //----------------------------------------------------------------------------

        //----------------------------------------------------------------------------
        //{ Digit
        //----------------------------------------------------------------------------

            unsigned int LongNumber::getDigit(size_t digitIndex) const
            {
                assert(ok());
                assert(digitIndex < size_);

                return number_[digitIndex];
            }

            LongNumber& LongNumber::setDigit(size_t digitIndex, unsigned int digit)
            {
                assert(ok());
                assert(digitIndex < size_);

                number_[digitIndex] = digit;

                assert(ok());

                return *this;
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Size
        //----------------------------------------------------------------------------

            size_t LongNumber::getSize() const
            {
                assert(ok());

                return size_;
            }

            LongNumber& LongNumber::setSize(size_t newSize)
            {
                assert(ok());

                unsigned int* newNumber = (unsigned int*) calloc(newSize, sizeof(*newNumber));
                assert(newNumber);

                for (size_t digit = 0; digit < newSize; digit++)
                {
                    assert(digit < newSize);
                    assert(newSize < MAX_ARRAY_SIZE);

                    newNumber[digit] = (digit < size_) ? number_[digit] : 0;
                }

                size_ = newSize;

                assert(number_ && newNumber);

                free(number_);

                number_ = newNumber;

                assert(ok());

                return *this;
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Notation system
        //----------------------------------------------------------------------------

            unsigned int LongNumber::getRadix() const
            {
                assert(ok());

                return radix_;
            }

            LongNumber& LongNumber::setRadix(unsigned int newRadix)
            {
                assert(ok());

                if (newRadix < radix_)
                {
                    for (size_t digit = 0; digit < size_; digit++)
                    {
                        assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

                        if (number_[digit] >= newRadix) number_[digit] = newRadix - 1;
                    }
                }

                radix_ = newRadix;

                return *this;
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Negative
        //----------------------------------------------------------------------------

            bool LongNumber::isNegative() const
            {
                assert(ok());

                return negative_;
            }

            LongNumber& LongNumber::setNegative(bool negative /*= true*/)
            {
                assert(ok());

                negative_ = negative;

                assert(ok());

                return *this;
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Decimal point
        //----------------------------------------------------------------------------

            size_t LongNumber::getDecimalPoint() const
            {
                assert(ok());

                return decimalPoint_;
            }

            LongNumber& LongNumber::setDecimalPoint(size_t decimalPoint)
            {
                assert(ok());
				assert(decimalPoint < size_);

                decimalPoint_ = decimalPoint;

                assert(ok());

                return *this;
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Integer part
        //----------------------------------------------------------------------------

            size_t LongNumber::getIntegerPart() const
            {
                assert(ok());

                return size_ - decimalPoint_;
            }

            LongNumber& LongNumber::setIntegerPart(size_t newIntegerPart)
            {
                // Checking input:

                    assert(ok());

                // Main algorithm:

                    size_t integerPart  = size_ - decimalPoint_;

                    shift(newIntegerPart - integerPart);

                // Checking output:

                    assert(ok());

                    return *this;

            }

        //}
        //----------------------------------------------------------------------------


		//----------------------------------------------------------------------------
		//{ Fractional part
		//----------------------------------------------------------------------------

			size_t LongNumber::getFractionalPart() const
			{
				assert(ok());

				return decimalPoint_;
			}

			LongNumber& LongNumber::setFractionalPart(size_t newFractionalPart)
			{
				// Checking input:

					assert(ok());

				// Creating the resources to work with:

					size_t newSize = newFractionalPart + getIntegerPart();

					unsigned int* newNumber = (unsigned int*) calloc(newSize, sizeof(*newNumber));
					assert(newNumber);

				// Main algorithm:

					for (size_t newNumberDigit = newSize - 1, digit = size_ - 1; digit < size_ && newNumberDigit < newSize;)
					{
						assert(digit < size_ && size_ < MAX_ARRAY_SIZE);
						assert(newNumberDigit < newSize && newSize < MAX_ARRAY_SIZE);

						newNumber[newNumberDigit] = number_[digit];

						if (digit == 0) break;
						if (newNumberDigit == 0) break;

						newNumberDigit--;
						digit--;
					}

					size_ = newSize;

					decimalPoint_ = newFractionalPart;

					free(number_);
					assert(newNumber);
					number_ = newNumber;

				// Checking output:

					assert(ok());

				// Return statement:

					return *this;
			}

		//}
		//----------------------------------------------------------------------------


    //}
    //----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
    //{ Functions
    //----------------------------------------------------------------------------

        //----------------------------------------------------------------------------
        //{ Service
        //----------------------------------------------------------------------------

			// Verification:

				bool LongNumber::ok() const
				{
					if (MODE == FINAL_MODE) return true;

					bool everythingOk = true;

					if (size_ >= MAX_ARRAY_SIZE)
					{
						puts("Number size is invalid.");
						everythingOk = false;
					}

					if (number_ == NULL)
					{
						puts("Digit array (number_) is a null pointer.");
						everythingOk = false;
					}

					for (size_t digit = 0; digit < size_; digit++)
					{
						if (number_[digit] >= radix_)
						{
							everythingOk = false;
						}
					}

					if (decimalPoint_ > size_)
					{
						puts("Decimal point is invalid.");
						everythingOk = false;
					}

					return everythingOk;
				}

	            void LongNumber::print() const
				{
					assert(ok());

					puts("\n============================");
					puts("LONG NUMBER");
					puts("============================");

					printf("Notation system == %d\n", radix_);

					puts("----------------------------");

					if (negative_) puts("Number is negative (-)");
					else           puts("Number is positive (+)");

					if (size_ != 0)
					{
						puts("----------------------------");
						puts("Number:");
						puts("----------------------------");

						for (size_t digit = size_ - 1; digit < size_; digit--)
						{
							printf("Number[%06d] == %06d\n", size_ - 1 - digit, number_[digit]);

							if (digit == decimalPoint_ && decimalPoint_ != 0) puts("Number[ here ] == .");
						}
					}

					puts("============================\n");
				}

				char* LongNumber::toRaw() const
				{
					// Checking input:

						assert(ok());

					// Creating the resourses to work with:

						size_t rawSize = size_ * 8 + static_cast<int>(negative_);

						char* rawStr = (char*) calloc(rawSize + 1, sizeof(*rawStr));
						assert(rawStr);

					// Main algorithm:

						size_t rawStrIndex = 0;

						if (negative_) rawStr[rawStrIndex++] = '-';

						for (size_t digit = size_ - 1; digit < size_; digit--)
						{
							assert(digit < size_);

							char* currentDigit = intToStr(number_[digit]);

							for (size_t currentDigitIndex = 0; currentDigitIndex < 8 && rawStrIndex < rawSize; currentDigitIndex++)
							{
								assert(currentDigitIndex < 8);

								rawStr[rawStrIndex++] = currentDigit[currentDigitIndex];
							}

							if (digit == 0) break;
						}

						rawStr[rawSize] = '\0';

					// Checking output:

						assert(ok());
						assert(rawStr);

					// Return statement:

						return rawStr;
				}

                char* LongNumber::toUserRaw() const
                {
                    // Checking input:

                        assert(ok());

                        if (radix_ > 16) return toRaw();

                    // Creating the resources to work with:

                        size_t rawSize = size_ + ((decimalPoint_ == 0) ? 1 : 2);

                        char* rawStr = (char*) calloc(rawSize, sizeof(*rawStr));
                        assert(rawStr);

                    // Main algorithm:

                        for (size_t digit = 0, rawStrIndex = rawSize - 2; digit < size_ && rawStrIndex < rawSize; digit++)
                        {
                            assert(digit < size_);
                            assert(rawStrIndex < rawSize);

                            if ((digit == decimalPoint_) && decimalPoint_ != 0)
                            {
                                rawStr[rawStrIndex] = '.';
                                rawStrIndex--;
                            }

                            rawStr[rawStrIndex] = intToChar(number_[digit]);

                            if (rawStrIndex == 0) break;
                            rawStrIndex--;
                        }

                        rawStr[rawSize - 1] = '\0';

                    // Checking output:

                        assert(rawStr);
                        assert(ok());

                    // Return statement:

                        return rawStr;
                }

			// Service:

				LongNumber& LongNumber::shift(int numberShift)
				{
					// Checking input:

						assert(ok());

					// Main algorithm:

						if (numberShift > 0)
						{
							if (static_cast<int>(decimalPoint_) >= numberShift) decimalPoint_ -= numberShift;
							else
							{
								size_t newSize = size_ + numberShift - decimalPoint_;

								unsigned int* newNumber = (unsigned int*)calloc(newSize, sizeof(*newNumber));
								assert(newNumber);

								for (size_t digit = size_ - 1; digit < size_ && digit < newSize; digit--)
								{
									assert(digit <= size_ && size_ < MAX_ARRAY_SIZE);
									assert(0 <= static_cast<int>(digit + numberShift - decimalPoint_));
									assert(digit + numberShift - decimalPoint_ <= newSize);
									assert(newSize < MAX_ARRAY_SIZE);

									newNumber[digit + numberShift - decimalPoint_] = number_[digit];

									if (digit == 0) break;
								}

								decimalPoint_ = 0;

								size_ = newSize;

								free(number_);
								assert(newNumber);
								number_ = newNumber;
							}
						}

						if (numberShift < 0)
						{
							if (static_cast<int>(decimalPoint_)-numberShift < static_cast<int>(size_)) decimalPoint_ -= numberShift;
							else
							{
								size_t newSize = decimalPoint_ - numberShift + 1;

								unsigned int* newNumber = (unsigned int*)calloc(newSize, sizeof(*newNumber));
								assert(newNumber);

								for (size_t digit = 0; digit < size_ && digit < newSize; digit++)
								{
									assert(digit <= size_   && size_   < MAX_ARRAY_SIZE);
									assert(digit <= newSize && newSize < MAX_ARRAY_SIZE);

									newNumber[digit] = number_[digit];
								}

								size_ = newSize;

								free(number_);
								assert(newNumber);
								number_ = newNumber;

								decimalPoint_ = size_ - 1;
							}
						}

					// Checking output:

						assert(ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::normalize()
				{
					// Checking input:

						assert(ok());

					// Defining left null border:

						size_t leftNullBorder = size_ - 1;
						for (; decimalPoint_ < leftNullBorder && leftNullBorder < size_; leftNullBorder--)
						{
							assert(decimalPoint_ < leftNullBorder && leftNullBorder < size_);

							if (number_[leftNullBorder] != 0) break;

							if (leftNullBorder == 0) break;
						}

					// Defining right null border:

						size_t rightNullBorder = 0;
						for (; rightNullBorder < decimalPoint_ && rightNullBorder < size_; rightNullBorder++)
						{
							assert(rightNullBorder < decimalPoint_ && rightNullBorder < size_);

							if (number_[rightNullBorder] != 0) break;
						}

					// Creating & filling new number array without unimportant nulls:

						if (leftNullBorder != size_ - 1 || rightNullBorder != 0)
						{
							size_t newSize = leftNullBorder - rightNullBorder + 1;

							unsigned int* newNumber = (unsigned int*)calloc(newSize, sizeof(*newNumber));
							assert(newNumber);

							for (size_t digit = rightNullBorder; digit <= size_ && digit <= leftNullBorder; digit++)
							{
								assert(digit <= size_ && digit <= leftNullBorder && size_ < MAX_ARRAY_SIZE);
								assert(digit - rightNullBorder <= newSize && newSize < MAX_ARRAY_SIZE);

								newNumber[digit - rightNullBorder] = number_[digit];
							}

							decimalPoint_ -= rightNullBorder;

							size_ = newSize;

							free(number_);

							assert(newNumber);
							number_ = newNumber;
						}

					// Checking output:

						assert(ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::randomize()
				{
					// Checking input:

						assert(ok());

					// Creating the resources to work with:
                        /*
						unsigned int* randomizedNumber = (unsigned int*) calloc(size_, sizeof(*randomizedNumber));
						assert(randomizedNumber);
                        */
					// Main algorithm:

                        /*
						if (rand() % 2)
						{
							LongNumber randomized = pow(2);

							size_t randomizeDigit = (size_ < 2) ? 0 : rand() % (size_ / 2);
							for (size_t digit = 0; digit < size_ && randomizeDigit < randomized.getSize();)
							{
								assert(digit < size_);
								assert(randomizeDigit < randomized.getSize());

								assert(size_ < MAX_ARRAY_SIZE);
								assert(randomized.getSize() < MAX_ARRAY_SIZE);

								randomizedNumber[digit] = randomized.getDigit(randomizeDigit);

								digit++;
								randomizeDigit++;
							}

							// This is called before the }
							//randomized.~LongNumber();
						}
						else
						{
							for (size_t digit = 0; digit < size_; digit++)
							{
								assert(digit < size_);
								assert(size_ < MAX_ARRAY_SIZE);

								randomizedNumber[digit] = rand() % radix_;
							}
						}

                        free(number_);
						assert(randomizedNumber);
						number_ = randomizedNumber;

						*/

						for (size_t digit = 0; digit < size_; digit++)
                        {
                            assert(digit < size_);
                            assert(size_ < MAX_ARRAY_SIZE);

                            number_[digit] = rand() % radix_;
                        }

					// Checking output:

						assert(ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::adapt(const LongNumber& number)
				{
					// Checking input:

						assert(ok());
						assert(number.ok());

					// Calculating new size & decimal point:

						size_t newDecimalPoint = maximum(decimalPoint_, number.getDecimalPoint());

						size_t newSize = newDecimalPoint + maximum(size_ - decimalPoint_, number.getSize() - number.getDecimalPoint());

					// Working with new modificated number array:

						unsigned int* newNumber = (unsigned int*)calloc(newSize, sizeof(*newNumber));
						assert(newNumber);

						for (size_t digit = 0, newNumberDigit = newDecimalPoint - decimalPoint_;
							digit          < size_ &&
							newNumberDigit < newSize;)
						{
							assert(digit          < size_   && size_   < MAX_ARRAY_SIZE);
							assert(newNumberDigit < newSize && newSize < MAX_ARRAY_SIZE);

							newNumber[newNumberDigit] = number_[digit];

							newNumberDigit++;
							digit++;
						}

					// Setting new number array, size & decimal point:

						size_ = newSize;

						decimalPoint_ = newDecimalPoint;

						free(number_);

						assert(newNumber);
						number_ = newNumber;

					// Checking output:

						assert(ok());
						assert(number.ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::setBothInteger(LongNumber* number)
				{
					assert(ok());
					assert(number->ok());

					int currentShift = maximum(decimalPoint_, number->getDecimalPoint());

					this->shift(currentShift);
					number->shift(currentShift);

					assert(ok());
					assert(number->ok());

					return *this;
				}

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Addition & substraction
        //----------------------------------------------------------------------------

            LongNumber LongNumber::sum(const LongNumber& number) const
            {
                // Checking input:

                    assert(ok());
                    assert(number.ok());

					if (radix_ != number.getRadix())
					{
						puts("Operating with numbers of different notation systems.");
					}

                // Creating the resources to operate with:

                    // Setting size && decimal point:

                        LongNumber summand0 = *this;
                        LongNumber summand1 = number;
                        LongNumber total    = LongNumber("[0]", radix_);

                        summand0.adapt(summand1);
                        summand1.adapt(summand0);

                        total.adapt(summand0);

                        if (!(summand0.isNegative() ^ summand1.isNegative())) total.setSize(total.getSize() + 1);

                        summand0.adapt(total);
                        summand1.adapt(total);

                    // Setting negativeness:

                        summand0.setNegative(false);
                        summand1.setNegative(false);

                        bool sumIsNegative = false;

                        if (negative_ && number.isNegative()) sumIsNegative = true;
                        else if (summand0 > summand1) sumIsNegative = negative_;
                        else if (summand0 < summand1) sumIsNegative = number.isNegative();

                        if (          negative_) summand0.inverseAndAdd();
                        if (number.isNegative()) summand1.inverseAndAdd();

                    // Pre-algorithm checking:

                        assert(summand0.ok());
                        assert(summand1.ok());
                        assert(total   .ok());

                // Main algorithm of addition:

                    unsigned int toNextDigit = 0;

                    size_t digit = 0;
                    for (;digit < summand0.getSize() &&
                          digit < summand1.getSize() &&
                          digit <    total.getSize();
                          digit++)
                    {
                        assert(digit <= summand0.getSize() && summand0.getSize() < MAX_ARRAY_SIZE);
                        assert(digit <= summand1.getSize() && summand1.getSize() < MAX_ARRAY_SIZE);
                        assert(digit <=    total.getSize() &&    total.getSize() < MAX_ARRAY_SIZE);

                        unsigned int curRes = summand0.getDigit(digit) + summand1.getDigit(digit) + toNextDigit;

                        total.setDigit(digit, curRes % radix_);

						if (curRes >= radix_) toNextDigit = 1;
						else toNextDigit = 0;
                    }

                    //-----------------------------------------------------------------------------

                    if (total.getSize() > summand0.getSize() && total.getSize() > summand1.getSize())
                    {
                        total.setDigit(digit, toNextDigit);
                    }

                    total.setNegative(sumIsNegative);

                    if (total.isNegative()) total.inverseAndAdd();

                    total.normalize();

                // Checking output:

                    assert(ok());
                    assert(number.ok());

                    // This happens just before the return:
                    //summand0.~LongNumber();
                    //summand1.~LongNumber();

				// Return statement:

                    return total;
            }

            void LongNumber::inverseAndAdd()
            {
                // Checking input:

                    assert(ok());

                // Main algorithm:

                    unsigned int toNextDigit = 1;

                    for (size_t digit = 0; digit < size_; digit++)
                    {
                        assert(digit <= size_);
                        assert(size_ <= MAX_ARRAY_SIZE);

                        unsigned int curRes = radix_ - 1 - number_[digit];

                        curRes += toNextDigit;

                        number_[digit] = curRes % radix_;

                        toNextDigit = curRes/radix_;
                        assert(toNextDigit < radix_);
                    }

                // Checking output:

                assert(ok());
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Multiplication
        //----------------------------------------------------------------------------

            LongNumber LongNumber::product(const LongNumber& number) const
            {
                // Checking input:

                    assert(ok());
                    assert(number.ok());

                    if (radix_ != number.getRadix())
					{
						printf("Operating with numbers of different notation systems.");
					}

                // Creating the resources to operate with:

                    LongNumber currentAddentum = number;
                    LongNumber toReturn = LongNumber("[0]", radix_);

                // Pre-algorithm checking:

                    assert(currentAddentum.ok());
                    assert(toReturn.ok());

                // Main algorithm:

                    for (size_t digit = size_ - 1; digit < size_; digit--)
                    {
                        assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

                        currentAddentum = number;
                        currentAddentum.setNegative(false);
                        currentAddentum.multiplyByDigit(number_[digit]);

                        assert(currentAddentum.ok());

                        toReturn += currentAddentum;

                        if (digit != 0) toReturn.shift(1);

                        if (digit == 0) break;
                    }

                // Setting negativeness && decimal point:

					toReturn.setDecimalPoint(0);
                    toReturn.shift(-static_cast<int>(decimalPoint_ + number.getDecimalPoint()));

                    toReturn.setNegative(negative_ ^ number.isNegative());

                    toReturn.normalize();

                // Checking output:

                    assert(ok());
                    assert(number.ok());
                    assert(toReturn.ok());

                // Return statement:

                    // This is called before the return satement:
                    //currentAddentum.~LongNumber();

                    return toReturn;
            }

            void LongNumber::multiplyByDigit(unsigned int factor)
            {
                // Checking input:

                    if (factor >= radix_)
                    {
                        puts("Trying to multiply this LongNumber object by digit from another notation system.");
                        assert(factor >= radix_);
                    }

                    assert(ok());

                // Pre-algorithm settings:

                    setSize(size_ + 1);

                // Main algorithm:

                    unsigned int toNextDigit = 0;

                    for (size_t digit = 0; digit < size_; digit++)
                    {
                        assert(digit < size_ && size_ < MAX_ARRAY_SIZE);
                        assert(number_[digit] < radix_);

						unsigned int curRes = number_[digit] * factor + toNextDigit;

						number_[digit] = curRes % radix_;

                        toNextDigit = curRes / radix_;

                        assert(toNextDigit < radix_);
                    }

                // Checking output:

                    assert(ok());
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Division
        //----------------------------------------------------------------------------

            LongNumber LongNumber::divideWithRemainder(const LongNumber& number) const
            {
                // Checking input:

                    assert(ok());
                    assert(number.ok());

					if (radix_ != number.getRadix())
					{
						puts("Operating with numbers of different notation systems.");
					}

                // Main algorithm:

                    LongNumber remainder = *this;
                    LongNumber module    = number;

					bool remainderIsNegative = remainder.isNegative() ^ module.isNegative();

					remainder.setNegative(false);
					module   .setNegative(false);

                    assert(remainder.ok());
                    assert(module	.ok());

                // Main algorithm:

					size_t remainderInitialSize = remainder.getSize();

					for (size_t remainderCurrentDigit = remainderInitialSize - 1; remainder >= module && remainderCurrentDigit < remainderInitialSize; remainderCurrentDigit--)
					{
						assert(remainderCurrentDigit < remainderInitialSize);
						assert(remainder >= module);

						remainder.divideDigit(remainderCurrentDigit, module);
					}

				// Post-algorithmic operations:

					if (remainderIsNegative) remainder = module - remainder;

                // Checking output:

                    assert(ok());
                    assert(number.ok());
                    assert(remainder.ok());

                // Return statement:

					// This is called before the return statement:
					//module.~LongNumber();

                    return remainder;
            }

            LongNumber LongNumber::divide(const LongNumber& number) const
            {
                // Checking input:

                    assert(ok());
                    assert(number.ok());

					if (radix_ != number.getRadix())
					{
						puts("Operating with numbers of different notation systems.");
					}

                // Creating the resources to work with:

                    LongNumber divident = *this;
                    LongNumber divisor  = number;
                    LongNumber quotient = LongNumber("[0].[0]", radix_);

                    divisor.setBothInteger(&divident);

                    divident.normalize();
                    divisor .normalize();

                    bool quotientNegativeness = divident.isNegative() ^ divisor.isNegative();

                    divident.setNegative(false);
                    divisor .setNegative(false);

                    //-----------------------------------------------------------------------------

					int finalShift = divident.getIntegerPart() - divisor.getSize();

					divident.shift(static_cast<int>(ACCURACY));

                // Main algorithm:

                    size_t dividentSize = divident.getSize();

                    for (size_t digit = dividentSize - 1; digit < dividentSize; digit--)
                    {
                        assert(digit < dividentSize);

                        quotient.setDigit(0, divident.divideDigit(digit, divisor));

                        if (digit != 0) quotient.shift(1);

                        if (digit == 0) break;
                    }

                // Post-algorithmic operations:

                    quotient.setNegative(quotientNegativeness);

                    //-----------------------------------------------------------------------------

					quotient.shift(finalShift  - static_cast<int>(quotient.getSize()) + 1);

                    quotient.normalize();

                // Checking output:

                    assert(ok());
                    assert(number.ok());
                    assert(quotient.ok());

                // Return statement:

                    return quotient;
            }

            unsigned int LongNumber::divideDigit(size_t currentDigit, const LongNumber& number)
            {
                // Checking input:

                    assert(ok());
                    assert(number.ok());

                    if (currentDigit >= size_) return 0;

                // Creating the resources to work with:

                    LongNumber divisor = number;

                    divisor.setIntegerPart(currentDigit + 1);

                    assert(divisor.ok());

                // Main algorithm:

                    unsigned int currentFactor = searchForDivisor(divisor);

                    if (currentFactor != 0)
                    {
                        divisor.multiplyByDigit(currentFactor);

                        *this -= divisor;
                    }

                // Checking output:

                    assert(ok());
                    assert(number.ok());

                    assert(currentFactor < radix_);

                // Return statement:

                    return currentFactor;
            }

            size_t LongNumber::searchForDivisor(const LongNumber& number) const
            {
                // Checking input:

                    assert(ok());
                    assert(number.ok());

                // Creating the resources to work with:

                    LongNumber divident = *this;
                    LongNumber divisor = number;

                    assert(divident.ok());
                    assert(divisor.ok());

                // Main algorithm:

                    unsigned int minFactor = 0;
                    for (unsigned int maxFactor = radix_; minFactor + 1 < maxFactor;)
                    {
                        assert(minFactor <= radix_);
                        assert(maxFactor <= radix_);

                        assert(minFactor + 1 < maxFactor);

                        //-----------------------------------------------------------------------------

                        unsigned int meanFactor = (minFactor + maxFactor) / 2;

                        //-----------------------------------------------------------------------------

                        LongNumber currentDivisor = divisor;

                        currentDivisor.multiplyByDigit(meanFactor);

                        assert(currentDivisor.ok());

                        //-----------------------------------------------------------------------------

                        if (currentDivisor < divident) minFactor = meanFactor;
                        if (currentDivisor > divident) maxFactor = meanFactor;

                        if (currentDivisor == divident)
                        {
                            minFactor = meanFactor;
                            break;
                        }

                        // This is called before the }:
                        //currentDivisor.~LongNumber();
                    }

                // Checking output:

                    assert(ok());
                    assert(number.ok());
                    assert(minFactor < radix_);

                // Return statement:

                    return minFactor;
            }

        //}
        //----------------------------------------------------------------------------


		//----------------------------------------------------------------------------
		//{ Factorial
		//----------------------------------------------------------------------------

			LongNumber LongNumber::factorial() const
			{
				// Checking input:

					assert(ok());

				// Creating the resources to work with:

					LongNumber toReturn = LongNumber("[1]", radix_);

					assert(toReturn.ok());

				// Main algorithm:

					if (*this > LongNumber("[1]", radix_))
					{
						for (LongNumber iteration = LongNumber("[2]", radix_); iteration <= *this; iteration++)
						{
							assert(iteration.ok());
							assert(toReturn.ok());

							toReturn *= iteration;
						}
					}

				// Checking output:

					assert(toReturn.ok());
					assert(ok());

				// Return statement:

					return toReturn;
			}


		//}
		//----------------------------------------------------------------------------


		//----------------------------------------------------------------------------
		//{ Power
		//----------------------------------------------------------------------------

			LongNumber LongNumber::pow(const int power) const
			{
				// Checking input:

					assert(ok());

				// Creating the resources to work with:

					LongNumber toReturn = LongNumber("[1]", radix_);

					assert(toReturn.ok());

				// Main algorithm:

					if (power < -1 || 1 < power)
					{
						int halfPower = power / 2;
						int additionalPower = power - halfPower * 2;

						LongNumber powered = pow(halfPower);
						assert(powered.ok());

						toReturn = powered * powered * pow(additionalPower);

						// This is called before the }
						//powered.~LongNumber();
					}
					else
					{
						if (power == -1) toReturn /= *this;

						if (power == 1) toReturn = *this;
					}

					toReturn.normalize();

				// Checking output:

					assert(toReturn.ok());

				// Return statement:

					return toReturn;
			}

		//}
		//----------------------------------------------------------------------------


		//----------------------------------------------------------------------------
		//{ Root
		//----------------------------------------------------------------------------


			LongNumber LongNumber::root(const unsigned int base) const
			{
				// Checking input:

					assert(ok());

					if (*this < LongNumber("[0]", radix_))
					{
						puts("The result is imaginary (and i'm too lazy to make it work)");

						assert(*this < LongNumber("[0]", radix_));
					}

				// Creating the resources to work with:

					LongNumber tree = *this;
					tree.setNegative(false);
					assert(tree.ok());

                    LongNumber minRoot = LongNumber("[1]", radix_);
                    LongNumber maxRoot = LongNumber("[1]", radix_);

                    if (tree < LongNumber("[1]", radix_)) minRoot = tree;
                    if (tree > LongNumber("[1]", radix_)) maxRoot = tree;

					assert(maxRoot.ok());
					assert(minRoot.ok());

					LongNumber previousMedianRoot = LongNumber("-[1]", radix_);
					LongNumber medianRoot		  = LongNumber("[0]", radix_);

					assert(previousMedianRoot.ok());
					assert(medianRoot		 .ok());

				// Main algorithm:

					while (previousMedianRoot != medianRoot)
					{
						assert(minRoot.ok());
						assert(maxRoot.ok());

						previousMedianRoot = medianRoot;

						medianRoot = (minRoot + maxRoot) / LongNumber("[2]", radix_);

						if (medianRoot.pow(base) <= tree) minRoot = medianRoot;
						else maxRoot = medianRoot;

						minRoot.setFractionalPart(ACCURACY);
						maxRoot.setFractionalPart(ACCURACY);

						medianRoot.setFractionalPart(ACCURACY);
					}

					medianRoot.normalize();

				// Checking output:

					assert(ok());
					assert(medianRoot.ok());

				// Return statement:

					// This is called before the return statement:
					//tree	 .~LongNumber();
					//maxRoot.~LongNumber();

					return medianRoot;

			}

		//}
		//----------------------------------------------------------------------------

    //}
    //----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
    //{ Operators
    //----------------------------------------------------------------------------

        //----------------------------------------------------------------------------
        //{ Assignment
        //----------------------------------------------------------------------------

			// Bitwise arithmetics:

				LongNumber& LongNumber::operator>>=(const unsigned int numberShift)
				{
					// Checking input:

						assert(ok());

					// Main algorithm:

						if (numberShift != 0)
						{
							for (size_t digit = 0; digit < size_; digit++)
							{
								assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

								if (digit >= numberShift)
								{
									number_[static_cast<int>(digit - numberShift)] = number_[digit];
									number_[digit] = 0;
								}
							}
						}

					// Checking output:

						assert(ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::operator<<=(const unsigned int numberShift)
				{
					// Checking input:

						assert(ok());

					// Main algorithm:

						if (numberShift != 0)
						{
							for (size_t digit = size_ - 1; 0 <= digit && digit < size_; digit--)
							{
								assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

								if (digit + numberShift < size_)
								{
									number_[digit + numberShift] = number_[digit];
									number_[digit] = 0;
								}

								if (digit == 0) break;
							}
						}

					// Checking output:

						assert(ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::operator&=(const LongNumber& number)
				{
					// Checking input:

						assert(ok());
						assert(number.ok());

					// Main algorithm:

						for (size_t digit = 0; digit < size_; digit++)
						{
							assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

							number_[digit] = minimum(number_[digit], number.getDigit(digit));
						}

					// Checking output:

						assert(ok());
						assert(number.ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::operator|=(const LongNumber& number)
				{
					// Checking input:

						assert(ok());
						assert(number.ok());

					// Main algorithm:

						for (size_t digit = 0; digit < size_; digit++)
						{
							assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

							number_[digit] = (number_[digit] + number.getDigit(digit)) / 2;
						}

					// Checking output:

						assert(ok());
						assert(number.ok());

					// Return statement:

						return *this;
				}

				LongNumber& LongNumber::operator^=(const LongNumber& number)
				{
					// Checking input:

						assert(ok());
						assert(number.ok());

					// Main algorithm:

						for (size_t digit = 0; digit < size_; digit++)
						{
							assert(digit < size_ && size_ < MAX_ARRAY_SIZE);

							if (number_[digit] && number.getDigit(digit)) number_[digit] = 0;
							else number_[digit] = maximum(number_[digit], number.getDigit(digit));
						}

					// Checking output:

						assert(ok());
						assert(number.ok());

					// Return statement:

						return *this;
				}

			// Regular arithmetics:

				LongNumber& LongNumber::operator=(const LongNumber& number)
				{
					assert(number.ok());

					size_ = number.getSize();

					radix_ = number.getRadix();

					negative_ = number.isNegative();

					decimalPoint_ = number.getDecimalPoint();

					free(number_);
					number_ = (unsigned int*) calloc(size_, sizeof(*number_));
					assert(number_);

					for (size_t digit = 0; digit < size_ && digit < number.getSize(); digit++)
					{
						assert(digit < size_ && digit < number.getSize());
						assert(size_ < MAX_ARRAY_SIZE && number.getSize() < MAX_ARRAY_SIZE);

						number_[digit] = number.getDigit(digit);
					}

					assert(ok());
					assert(number.ok());

					return *this;
				}

				LongNumber& LongNumber::operator+=(const LongNumber& number)
				{
					assert(ok());
					assert(number.ok());

					*this = *this + number;

					assert(ok());
					assert(number.ok());

					return *this;
				}

				LongNumber& LongNumber::operator-=(const LongNumber& number)
				{
					assert(ok());
					assert(number.ok());

					*this = *this - number;

					assert(ok());
					assert(number.ok());

					return *this;
				}

				LongNumber& LongNumber::operator*=(const LongNumber& number)
				{
					assert(ok());
					assert(number.ok());

					*this = *this * number;

					assert(ok());
					assert(number.ok());

					return *this;
				}

				LongNumber& LongNumber::operator/=(const LongNumber& number)
				{
					assert(ok());
					assert(number.ok());

					*this = *this / number;

					assert(ok());
					assert(number.ok());

					return *this;
				}

				LongNumber& LongNumber::operator%=(const LongNumber& number)
				{
					assert(ok());
					assert(number.ok());

					*this = *this % number;

					assert(ok());
					assert(number.ok());

					return *this;
				}

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Increment/decrement
        //----------------------------------------------------------------------------

            // Prefix:

                LongNumber& LongNumber::operator++()
                {
                    assert(ok());

                    *this += LongNumber("[1]", radix_);

                    assert(ok());
                    return *this;
                }

                LongNumber& LongNumber::operator--()
                {
                    assert(ok());

                    *this -= LongNumber("[1]", radix_);

                    assert(ok());
                    return *this;
                }

            // Postfix:

                LongNumber LongNumber::operator++(int)
                {
                    assert(ok());

                    LongNumber toReturn = *this;

                    *this += LongNumber("[1]", radix_);

                    assert(ok());
                    assert(toReturn.ok());
                    return toReturn;
                }

                LongNumber LongNumber::operator--(int)
                {
                    assert(ok());

                    LongNumber toReturn = *this;

                    *this -= LongNumber("[1]", radix_);

                    assert(ok());
                    assert(toReturn.ok());
                    return toReturn;
                }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Arithmetic
        //----------------------------------------------------------------------------

			// Bitwise arithmetics:

				LongNumber LongNumber::operator~() const
				{
					// Checking input:

						assert(ok());

					// Main algorithm:

						LongNumber toReturn = *this;
						assert(toReturn.ok());

						for (size_t digit = 0; digit < toReturn.getSize(); digit++)
						{
							assert(digit <= toReturn.getSize());
							assert(toReturn.getSize() <= MAX_ARRAY_SIZE);

							toReturn.setDigit(digit, toReturn.getRadix() - 1 - toReturn.getDigit(digit));
						}

					// Checking output:

						assert(ok());
						assert(toReturn.ok());

					// Return statement:

						return toReturn;
				}

				LongNumber LongNumber::operator>>(const unsigned int numberShift) const
				{
					assert(ok());

					LongNumber toReturn = *this;
					toReturn >>= numberShift;

					assert(ok());
					assert(toReturn.ok());

					return toReturn;
				}

				LongNumber LongNumber::operator<<(const unsigned int numberShift) const
				{
					assert(ok());

					LongNumber toReturn = *this;
					toReturn <<= numberShift;

					assert(ok());
					assert(toReturn.ok());

					return toReturn;
				}

				LongNumber LongNumber::operator&(const LongNumber& number) const
				{
					assert(ok());
					assert(number.ok());

					LongNumber toReturn = *this;
					toReturn &= number;

					assert(ok());
					assert(number.ok());
					assert(toReturn.ok());

					return toReturn;
				}

				LongNumber LongNumber::operator|(const LongNumber& number) const
				{
					assert(ok());
					assert(number.ok());

					LongNumber toReturn = *this;
					toReturn |= number;

					assert(ok());
					assert(number.ok());
					assert(toReturn.ok());

					return toReturn;
				}

				LongNumber LongNumber::operator^(const LongNumber& number) const
				{
					assert(ok());
					assert(number.ok());

					LongNumber toReturn = *this;
					toReturn ^= number;

					assert(ok());
					assert(number.ok());
					assert(toReturn.ok());

					return toReturn;
				}

            // Regular arithmetics:

				LongNumber LongNumber::operator+() const
				{
					assert(ok());

					LongNumber toReturn = *this;

					assert(ok());
					assert(toReturn.ok());

					return toReturn;
				}

				LongNumber LongNumber::operator-() const
				{
					assert(ok());

					LongNumber toReturn = *this;
					toReturn.setNegative(!toReturn.isNegative());

					assert(ok());
					assert(toReturn.ok());

					return toReturn;
				}

                LongNumber LongNumber::operator+(const LongNumber& number) const
                {
					assert(ok());
					assert(number.ok());

                    LongNumber toReturn = this->sum(number);

                    assert(toReturn.ok());
					assert(ok());
					assert(number.ok());

                    return toReturn;
                }

                LongNumber LongNumber::operator-(const LongNumber& number) const
                {
					assert(ok());
					assert(number.ok());

                    LongNumber minusNumber = number;
                    assert(minusNumber.ok());

                    minusNumber.setNegative(!minusNumber.isNegative());

                    LongNumber toReturn = this->sum(minusNumber);

                    assert(toReturn.ok());
					assert(ok());
					assert(number.ok());

                    // minusNumber destructor is automatically called before return statement:
                    //minusNumber.~LongNumber();

                    return toReturn;
                }

                LongNumber LongNumber::operator*(const LongNumber& number) const
                {
                    assert(ok());
					assert(number.ok());

                    LongNumber toReturn = this->product(number);

                    assert(toReturn.ok());
					assert(ok());
					assert(number.ok());

                    return toReturn;
                }

                LongNumber LongNumber::operator/(const LongNumber& number) const
                {
					assert(ok());
					assert(number.ok());

                    LongNumber toReturn = this->divide(number);

                    assert(toReturn.ok());
					assert(ok());
					assert(number.ok());

                    return toReturn;
                }

				LongNumber LongNumber::operator%(const LongNumber& number) const
				{
					assert(ok());
					assert(number.ok());

					LongNumber toReturn = divideWithRemainder(number);

					assert(toReturn.ok());
					assert(ok());
					assert(number.ok());

					return toReturn;
				}

		//}
        //----------------------------------------------------------------------------


		//----------------------------------------------------------------------------
		//{ Logical
		//----------------------------------------------------------------------------

			bool LongNumber::operator!() const
			{
				assert(ok());

				return negative_;
			}

			bool LongNumber::operator&&(const LongNumber& number) const
			{
				assert(ok());
				assert(number.ok());

				return (!negative_) && (!number.isNegative());
			}

			bool LongNumber::operator&&(const bool statement) const
			{
				assert(ok());

				return (!negative_) && statement;
			}

			bool LongNumber::operator||(const LongNumber& number) const
			{
				assert(ok());
				assert(number.ok());

				return (!negative_) || (!number.isNegative());
			}

			bool LongNumber::operator||(const bool statement) const
			{
				assert(ok());

				return (!negative_) || statement;
			}

		//}
		//----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Comparison
        //----------------------------------------------------------------------------

            // Foundational operators:

                bool LongNumber::operator==(const LongNumber& number) const
                {
					// Checking input:

						assert(ok());
						assert(number.ok());

						if (radix_ != number.getRadix())
						{
							puts("Comparing numbers of different notation systems.");
						}

                    // Creating resourses to work with:

						LongNumber thisOne    = *this;
						LongNumber anotherOne = number;

						assert(thisOne   .ok());
						assert(anotherOne.ok());

						thisOne   .adapt(anotherOne);
						anotherOne.adapt(   thisOne);

						bool toReturn = true;

                    // Main algorithm:

						bool theSame = true;
						for (size_t digit = thisOne.getSize() - 1;
							 theSame &&
							 digit < thisOne   .getSize() &&
							 digit < anotherOne.getSize();
							 digit--)
						{
							assert(digit < thisOne   .getSize() && thisOne   .getSize() < MAX_ARRAY_SIZE);
							assert(digit < anotherOne.getSize() && anotherOne.getSize() < MAX_ARRAY_SIZE);

							if (thisOne.getDigit(digit) != anotherOne.getDigit(digit))
							{
								toReturn = false;
								break;
							}

							if (digit == 0) break;
						}

						if (thisOne.isNegative() != anotherOne.isNegative() || thisOne.getDecimalPoint() != anotherOne.getDecimalPoint()) toReturn = false;

                    // Checking output:

						assert(ok());
						assert(number.ok());

					// Return statement:

						// This happens just before the return:
						//thisOne.~LongNumber();
						//anotherOne.~LongNumber();

	                    return toReturn;
                }

                bool LongNumber::operator<(const LongNumber& number) const
                {
                    // Checking input:

						assert(ok());
						assert(number.ok());

						if (radix_ != number.getRadix())
						{
							puts("Comparing numbers of different notation systems.");
						}

                    // Creating resourses to work with:

						LongNumber thisOne    = *this;
						LongNumber anotherOne = number;

						thisOne   .adapt(anotherOne);
						anotherOne.adapt(   thisOne);

						assert(thisOne   .ok());
						assert(anotherOne.ok());

						bool toReturn = false;

                    // Main algorithm:

						bool theSame = true;
						for (size_t digit = thisOne.getSize() - 1;
							 theSame &&
							 digit < thisOne   .getSize() &&
							 digit < anotherOne.getSize();
							 digit--)
						{
							assert(digit < thisOne   .getSize() && thisOne   .getSize() < MAX_ARRAY_SIZE);
							assert(digit < anotherOne.getSize() && anotherOne.getSize() < MAX_ARRAY_SIZE);

							if (thisOne.getDigit(digit) < anotherOne.getDigit(digit))
							{
								toReturn = true;
								break;
							}

							if (thisOne.getDigit(digit) > anotherOne.getDigit(digit))
							{
								toReturn = false;
								break;
							}

							if (digit == 0) break;
						}

						if (thisOne.isNegative() && anotherOne.isNegative() && thisOne != anotherOne) toReturn = !toReturn;

                    // checking output:

						assert(ok());
						assert(number.ok());

					// Return statement:

						// This happens just before the return:
						//thisOne.~LongNumber();
						//anotherOne.~LongNumber();

						return toReturn;
                }

            // Expressed operators:

                bool LongNumber::operator!=(const LongNumber& number) const
                {
                    assert(ok());
                    assert(number.ok());

                    bool toReturn = !(*this == number);

                    assert(ok());
                    assert(number.ok());

                    return toReturn;
                }

                bool LongNumber::operator>(const LongNumber& number) const
                {
                    assert(ok());
                    assert(number.ok());

                    bool toReturn = number < *this;

                    assert(ok());
                    assert(number.ok());

                    return toReturn;
                }

                bool LongNumber::operator<=(const LongNumber& number) const
                {
                    assert(ok());
                    assert(number.ok());

					bool toReturn = !(number < *this);

                    assert(ok());
                    assert(number.ok());

                    return toReturn;
                }

                bool LongNumber::operator>=(const LongNumber& number) const
                {
                    assert(ok());
                    assert(number.ok());

					bool toReturn = !(*this < number);

                    assert(ok());
                    assert(number.ok());

                    return toReturn;
                }

        //}
        //----------------------------------------------------------------------------


		//----------------------------------------------------------------------------
		//{ Access
		//----------------------------------------------------------------------------

			unsigned int LongNumber::operator[](const size_t digitIndex) const
			{
				// Checking input:

					assert(ok());

					if (digitIndex >= size_)
					{
						puts("The requested digit is outside of stored digits");
					}

				// Return statement:

					return (digitIndex < size_) ? number_[digitIndex] : 0;
			}

		//}
		//----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ User-defined literals
        //----------------------------------------------------------------------------

            LongNumber operator"" _Long(const unsigned long long int number)
            {
                return LongNumber(static_cast<signed long long int>(number), 10);
            }

			LongNumber operator"" _Long(const char* number)
            {
                return LongNumber(number, 10);
            }

        //}
        //----------------------------------------------------------------------------

    //}
    //----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Str -> Int && Int -> Str
//----------------------------------------------------------------------------

    unsigned int ML_atoi(char* number, unsigned int radix)
    {
        assert(number);

        int toReturn = 0;

        for (size_t i = 0; number[i] != 0; i++)
        {
            assert(number[i] != 0);

            if (i != 0) toReturn *= radix;

            toReturn += charToInt(number[i]);
        }

        assert(number);

        return toReturn;
    }

    char* ML_itoa(int number, unsigned int radix)
    {
        char* toReturn = (char*) calloc(static_cast<size_t>(log(number) / log(radix) + 1), sizeof(*toReturn));
		assert(toReturn);

        size_t i = 0;
        for (; number != 0; i++)
        {
            toReturn[i] = intToChar(number % radix);

            number /= radix;
        }

		assert(toReturn);
        toReturn[i] = '\0';

        reverseStr(toReturn);

        assert(toReturn);

        return toReturn;
    }


//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Additional functions
//----------------------------------------------------------------------------

	char* intToStr(unsigned int integer)
	{
		char* str = (char*) calloc(18, sizeof(*str));
		assert(str);

		str[0] = '[';
		str[7] = ']';

		for (size_t i = 6; 0 < i && i < 7; i--)
		{
			str[i] = static_cast<char>(NUMBER_BASE + integer % 10);

			integer /= 10;
		}

		return str;
	}

	//----------------------------------------------------------------------------

    unsigned int maximum(unsigned int numberA, unsigned int numberB)
    {
        if (numberA >= numberB) return numberA;
        else return numberB;
    }

	unsigned int minimum(unsigned int numberA, unsigned int numberB)
	{
		if (numberA <= numberB) return numberA;
		else return numberB;
	}

	//----------------------------------------------------------------------------

    int ML_strLen(const char* myString)
    {
        assert(myString);

        for (int i = 0; ; i++)
        {
            if (!myString[i]) return i;
        }

        return -1;
    }

    void reverseStr(char* myString)
    {
        assert(myString);

        size_t strLen = ML_strLen(myString);

        for (size_t left = 0, right = strLen - 1; left < right;)
        {
            assert( left < strLen);
            assert(right < strLen);

            char tmp       = myString[left];
            myString[left] = myString[right];
            myString[right] = tmp;

            left++;
            right--;
        }

        assert(myString);
    }

	//----------------------------------------------------------------------------

    char toUpper(char charecter)
    {
        if (SMALL_LETTER_BASE <= charecter && SMALL_LETTER_END  >= charecter)
        {
            return static_cast<char>(BIG_LETTER_BASE + (charecter - SMALL_LETTER_BASE));
        }

        return charecter;
    }

    unsigned int charToInt(char charecter)
    {
        charecter = toUpper(charecter);

        if (BIG_LETTER_BASE <= charecter && BIG_LETTER_END  >= charecter)
        {
            return (NUMBER_END - NUMBER_BASE + 1) + charecter - BIG_LETTER_BASE;
        }

        if (NUMBER_BASE <= charecter && charecter <= NUMBER_END)
        {
            return charecter - NUMBER_BASE;
        }

        return 0;
    }

    char intToChar(unsigned int integer)
    {
        if (integer <= 9) return static_cast<char>(integer + NUMBER_BASE);

        return static_cast<char>((integer - 10) + BIG_LETTER_BASE);
    }

//}
//----------------------------------------------------------------------------

#endif
