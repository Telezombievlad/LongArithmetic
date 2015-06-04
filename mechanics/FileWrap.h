#ifndef __FILE_WRAP_H__
#define __FILE_WRAP_H__


//----------------------------------------------------------------------------
//{ FileWrap
//----------------------------------------------------------------------------

    class FileWrap
    {
        public:
            // Constructor & destructor:

                 FileWrap(const char* fileName);
                ~FileWrap();

            // Getters & setters:


            // Functions:

                bool ok();

                char* readFromFile();
                void   writeToFile(const char* toWrite, bool append = true);

        private:
            const char* fileName_;

    };


    //----------------------------------------------------------------------------
    //{ Constructor & destructor
    //----------------------------------------------------------------------------

        FileWrap::FileWrap(const char* fileName) :
            fileName_ (fileName)
        {
            assert(ok());
        }

        FileWrap::~FileWrap()
        {}

    //}
    //----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
    //{ Functions
    //----------------------------------------------------------------------------

        bool FileWrap::ok()
        {
            if (MODE == FINAL_MODE) return true;

            if (fileName_ == NULL || *fileName_ == '\0') return false;

            return true;
        }

        char* FileWrap::readFromFile()
        {
            assert(ok());

            FILE* openedFile = fopen(fileName_, "r");
            assert(openedFile);

            int fileLength = _filelength(_fileno(openedFile));

            char* toReturn = (char*) calloc(fileLength + 1, sizeof(*toReturn));
			assert(toReturn);

            fread(toReturn, fileLength, sizeof(*toReturn), openedFile);

			assert(toReturn);
            toReturn[fileLength] = '\0';

            assert(toReturn);

            return toReturn;
        }

        void FileWrap::writeToFile(const char* toWrite, bool append /*= true*//* true - fopen(fileName_, "a") is used, false - fopen(fileName_, "w") is used*/)
        {
            assert(toWrite);
            assert(ok());

            FILE* openedFile = fopen(fileName_, (append) ? "a" : "w");
            assert(openedFile);

            fwrite(toWrite, strlen(toWrite), sizeof(*toWrite), openedFile);
        }

    //}
    //----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------

#endif
