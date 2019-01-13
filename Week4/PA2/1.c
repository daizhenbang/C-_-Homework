    Complex& operator=(string s){
        size_t pos1 = s.find("+");
        size_t pos2 = s.find("i");
        string sReal = s.substr(0,pos1);
        string sImagine = s.substr(pos1+1,pos2);
        r = atof(sReal.c_str());
        i = atof(sImagine.c_str());
        return *this;
    }

