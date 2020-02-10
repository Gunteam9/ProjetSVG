Pour créer un cbor il faut faire comme ça : 
    et include : #include "../cbor11/cbor11.hpp"


    cbor item = cbor::map {{"sun_x","20"}, {"sun_y","30"}} ;

    cbor::binary encodedItem = cbor::encode(item);
    
C'est le encodedItem que vous allez envoyer dans le socket