namespace luambda
{
    class entity
    {
    public:
        entity();
        entity(std::nullptr_t);

        entity(edict_t* ent);
        entity(const entvars_t* pev);
        static entity find_by_index(int index);
        bool is_valid();
        void set_origin(const vec3_t& origin);
        void set_velocity(const vec3_t& velocity);
        edict_t* raw_entity();
        edict_t* edict();
        entvars_t* pev();
        entvars_t* entvars();
    };
};
