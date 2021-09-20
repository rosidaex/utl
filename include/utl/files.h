#include <utl/includes.h>

namespace Files {
    bool Usable_File(
        std::string File_Name
    ) {
            std::ifstream File(File_Name);
            if(!File.is_open()) {
                return false;
            }
            File.close();
            return true;
    }
    class File_Unusable : std::exception {
    public:
        std::string _File_Name;
        File_Unusable(
            std::string File_Name
        ) { _File_Name = File_Name; }
    };
    void Throw_If_Not_Usable(
        std::string File_Name
    ) {
        if(!Usable_File(File_Name)) {
            File_Unusable _Exception(File_Name);
            std::cout << 
                        "_File_Name: " << 
                        _Exception._File_Name << 
                        "\n";
            throw _Exception;
        }
    }
    std::string Read_File(
        std::string File_Name
    ) {
            Throw_If_Not_Usable(File_Name);
            std::ifstream   File(File_Name);
            std::string     Line;
            std::string     Text;
            while(!File.eof()) {
                std::getline(File, Line);
                Text += Line;
            }
            File.close();
            return Text;
    }
    std::vector<std::string> Read_File_Lines(
        std::string File_Name
    ) {
            Throw_If_Not_Usable(File_Name);
            std::ifstream               File(File_Name);
            std::string                 Line;
            std::vector<std::string>    Lines;
            while(!File.eof()) {
                std::getline(File, Line);
                Lines.push_back(Line);
            }
            File.close();
            return Lines;
    }
    template <typename T> int Write_File(
        std::string File_Name,
        T           Output,
        bool        Append = false,
        bool        Throw = false
    ) {
            if(Throw) Throw_If_Not_Usable(File_Name);
            std::ofstream File;
            if(Append) {
                File.open(File_Name, std::ios::app);
            } else {
                File.open(File_Name);
            }
            File << Output;
            File.close();
            return 0;
    }
    double Size_Of_File_Double(
        std::string File_Name,
        int         Size_Notation
    ) {
            Throw_If_Not_Usable(File_Name);
            std::ifstream File(File_Name, std::ios::binary | std::ios::ate);
            double Size = File.tellg();
            File.close();
            switch (Size_Notation) {
                case 0: return Size/8;
                case 1: return Size/1024;
                case 2: return Size/1024/1024;
                case 3: return Size/1024/1024/1024;
            }
    }
    int Size_Of_File_Int(
        std::string File_Name,
        int         Size_Notation
    ) {
            Throw_If_Not_Usable(File_Name);
            std::ifstream File(File_Name, std::ios::binary | std::ios::ate);
            int Size = File.tellg();
            File.close();
            switch (Size_Notation) {
                case 0: return Size/8;
                case 1: return Size/1024;
                case 2: return Size/1024/1024;
                case 3: return Size/1024/1024/1024;
            }
    }
    std::string Head_File(
        std::string File_Name,
        int Count
    ) {
            Throw_If_Not_Usable(File_Name);
            std::string File_Contents = Read_File(File_Name);
            if(File_Contents.size() < Count) {
                throw std::out_of_range(File_Name);
            }
            return File_Contents.substr(0, Count);
    }
}