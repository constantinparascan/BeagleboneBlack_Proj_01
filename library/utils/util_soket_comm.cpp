

class Util_comm_processor
{
  
private:
    
    std::vector<string *> str_vect_key_pub_rec;
    
    std::vector<string *> str_vect_key_priv_local;
    std::vector<string *> str_vect_key_pub_local;
    
    
    string* str_message;
    
    
public:

    void Push_Message(string* challenge);
    
    int Decode_Request(void);

};


void Util_comm_processor::Push_Message( string* challenge )
{
    
}

int Util_comm_processor::Decode_Request(void)
{
    
}