#include "Protocol.h"
#include <string.h>

enum{
  HEAD1_ST,
  HEAD2_ST,
  NUM_ST,
  LEN_ST,
  DATA_ST,
  CRC_ST
};

void PackPacket(PackFrame * frame, uint8_t * Src, uint8_t Length)
{
    frame->len = Length + 1;
    
    memcpy((void*)frame->data, Src, Length);
    char crc = 0;
    for(int i = 0; i < Length; i++)
        crc += frame->data[i];
    frame->data[Length] = crc;
}

SimplePack::SimplePack() {

}

SimplePack::~SimplePack() {

}

void SimplePack::Reset()
{
    lenGet  = 0;
    state   = 0;
    sanity  = 0;
    crc   = 0;
}

int SimplePack::Parse(char byteIn){

  switch(state){
  case HEAD1_ST:{
    if (byteIn == 0x77)
      state = HEAD2_ST;
  }break;
  case HEAD2_ST:{
    if (byteIn == 0x66)
      state =  NUM_ST;

  }break;
  case NUM_ST:{
    packFrameIn.num = byteIn;
    state = LEN_ST;
  }break;
  case LEN_ST:{
    packFrameIn.len = byteIn;
    state = DATA_ST;
  }break;
  case DATA_ST:{
    
    if ( lenGet < (packFrameIn.len - 1) ){
      packFrameIn.data[lenGet] = byteIn;
      crc += byteIn;
    }
    if ( lenGet == (packFrameIn.len - 1) ){
      packFrameIn.data[lenGet] = byteIn;
      lenGet  = 0;
      state   = 0;
      sanity  = 0;
      if (crc == byteIn){
        crc = 0;
        return 1;
      }else{
        crc = 0;
        return -1;
      }
    }
  lenGet++; 
  }break;
  }
  if(sanity++ > 260){
    state = 0;
    sanity = 0;
    return -1;
  }
  return 0;
}
