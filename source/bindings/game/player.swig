namespace luambda
{
    class player : public entity
    {
    public:
        using entity::entity;
        static player find_by_index(int index);
        void print_console(const char* message);
    };
};
