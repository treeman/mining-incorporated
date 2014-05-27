
namespace scene {

    struct ObjectInfo {
        virtual ~ObjectInfo() { }
        virtual unique_ptr<Object> creat_object() const;

        string key;
    };
}

