#define SDL_MAIN_HANDLED
#include "dictionary.h"
#include "aiv_unit_test.h"

TEST(dictionary){
    dictionary_t* dict = new_dict(10);
    ASSERT_THAT(dict->hash_map[0]==0);
    ASSERT_THAT(dict->hash_map_size==10);
}

TEST(test_hashing){
    int hash=hashing("key",10);
    ASSERT_THAT(hash==9);
}

TEST(insert_item){
    dictionary_t* dict = new_dict(10);
    add_to_dictionary(dict,"key",sizeof("key"),"value");
    int hash = hashing("key", 10);
    ASSERT_THAT(dict->hash_map[hash]->key_length==sizeof("key"));
}

TEST(test_get_value){
    dictionary_t* dict = new_dict(10);
    add_to_dictionary(dict,"key",sizeof("key"),"value");
    char* value=get_value(dict,"key",sizeof("key"));
    ASSERT_THAT(value=="value");
}

TEST(remove_key_value_test){
    dictionary_t* dict = new_dict(10);
    add_to_dictionary(dict,"key",sizeof("key"),"value");
    remove_key_value_pair(dict,"key",sizeof("key"));
    void* value=get_value(dict,"key",sizeof("key"));
    ASSERT_THAT(value==NULL);
}

int main(int argc, char **argv)
{
    RUN_TEST(dictionary); 
    RUN_TEST(test_hashing);   
    RUN_TEST(insert_item);
    RUN_TEST(test_get_value);
    RUN_TEST(remove_key_value_test);
    return 0;
}