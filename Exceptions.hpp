
namespace FileExceptions{

class OpenFileExceptionForReading{
public:
    /**
     * @brief The function prints appopriate error message 
     * if file is in a bad state.
     * 
     */
    void printException();
};

class ReadFileException{
public:
    /**
     * @brief The function prints appopriate error message 
     * if error occurred while reading the file.
     * 
     */
    void printException();
};

class OpenFileExceptionForWriting{
public:
    /**
     * @brief The function prints appopriate error message 
     * if file is in a bad state.
     * 
     */
    void printException();
};

class WriteFileException{
public:
    /**
     * @brief The function prints appopriate error message 
     * if error occurred while writing to file.
     * 
     */
    void printException();
};
}







