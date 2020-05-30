#pragma once

namespace mk1 {
namespace fs {

    class File {
      public:
        ~File();

        File(const File&) = delete;
        void operator=(const File&) = delete;

        void seek(int64_t offset);
        int64_t tell() const;

        int64_t size() const;

      protected:
        File(const char* filename, const char* mode);

        template <typename T>
        T* get_handle()
        {
            return (T*)_file;
        }

      private:
        void* _file;
    };

    class WriteFile : public File {
      public:
        WriteFile(const char* filename);
        WriteFile(const string& filename) : WriteFile(filename.c_str()) {}
        ~WriteFile();

        void write(const void* buffer, const size_t len);
    };

    class ReadFile : public File {
      public:
        ReadFile(const char* filename);
        ReadFile(const string& filename) : ReadFile(filename.c_str()) {}
        ~ReadFile();

        size_t read(void* buffer, const size_t len);
    };

    void init_fs(const string& org, const string& app);

    const string& get_home();
    const string& get_base();

} // fs
} // mk1
