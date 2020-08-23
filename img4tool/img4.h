//
//  img4.h
//  img4tool
//
//  Created by tihmstar on 15.06.16.
//  Copyright © 2016 tihmstar. All rights reserved.
//

#ifndef img4_h
#define img4_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <plist/plist.h>
#define LEN_XTND  0x80		/* Indefinite or long form */
typedef unsigned char byte;

#define putStr(s,l) printf("%.*s",(int)l,s)

//TagClass
#define kASN1TagClassUniversal       0
#define kASN1TagClassApplication     1
#define kASN1TagClassContextSpecific 2
#define kASN1TagClassPrivate        3

//primitive
#define kASN1Primitive  0
#define kASN1Contructed 1

//tagNumber
#define kASN1TagEnd_of_Content	0
#define kASN1TagBOOLEAN         1
#define kASN1TagINTEGER         2
#define kASN1TagBIT             3
#define kASN1TagOCTET           4
#define kASN1TagNULL            5
#define kASN1TagOBJECT          6
#define kASN1TagObject          7
#define kASN1TagEXTERNAL        8
#define kASN1TagREAL            9
#define kASN1TagENUMERATED      10 //0x0A
#define kASN1TagEMBEDDED        11 //0x0B
#define kASN1TagUTF8String      12 //0x0C
#define kASN1TagRELATIVE_OID	13 //0x0D
#define kASN1TagReserved        (14 | 15) //(0x0E | 0x0F)
#define kASN1TagSEQUENCE        16 //0x10
#define kASN1TagSET             17 //0x11
#define kASN1TagNumericString	18 //0x12
#define kASN1TagPrintableString	19 //0x13
#define kASN1TagT61String       20 //0x14
#define kASN1TagVideotexString	21 //0x15
#define kASN1TagIA5String       22 //0x16
#define kASN1TagUTCTime         23 //0x17
#define kASN1TagGeneralizedTime	24 //0x18
#define kASN1TagGraphicString	25 //0x19
#define kASN1TagVisibleString	26 //0x1A
#define kASN1TagGeneralString	27 //0x1B
#define kASN1TagUniversalString	28 //0x1C
#define kASN1TagCHARACTER       29 //0x1D
#define kASN1TagBMPString       30 //0x1E
#define kASN1TagPrivate   (char)0xff

typedef struct{
    byte tagNumber : 5;
    byte isConstructed : 1;
    byte tagClass : 2;
}t_asn1Tag;

typedef struct{
    byte len : 7;
    byte isLong : 1;
}t_asn1Length;

typedef struct{
    size_t dataLen;
    size_t sizeBytes;
} t_asn1ElemLen;

typedef struct{
    byte num : 7;
    byte more : 1;
}t_asn1PrivateTag;


#ifndef __cplusplus
typedef enum{
    false,
    true
}bool;
#endif

//asn1
t_asn1ElemLen asn1Len(const char buf[4]);
char *ans1GetString(char *buf, char **outString, size_t *strlen);
int asn1ElementsInObject(const char *buf);
char *asn1ElementAtIndex(const char *buf, int index);


char *getValueForTagInSet(char *set, uint32_t tag);


//img4
void printIM4P(char *buf);
void printIM4R(char *buf);
void printIM4M(char *buf, bool printAll);
void printMANB(char *buf, bool printAll);

int sequenceHasName(const char *buf, char *name);
int getSequenceName(const char *buf,char**name, size_t *nameLen);
size_t asn1GetPrivateTagnum(t_asn1Tag *tag, size_t *sizebytes);
int extractFileFromIM4P(char *buf, const char *dstFilename);
void printElemsInIMG4(char *buf, bool printAll, bool im4pOnly);

char *getElementFromIMG4(char *buf, char* element);
int extractElementFromIMG4(char *buf, char* element, const char *dstFilename);
char *makeIMG4(char *im4p, char *im4m, char *im4r, size_t *size);

char *getBNCHFromIM4M(const char* im4m, size_t *nonceSize);
char *getIM4PFromIMG4(char *buf);
char *getIM4MFromIMG4(char *buf);

int replaceNameInIM4P(char *buf, const char *newName);
int verifyIM4MSignature(const char *buf);
int verifyIMG4(char *buf, plist_t buildmanifest);
    
plist_t getBuildIdentityForIM4M(const char *buf, const plist_t buildmanifest);
void printGeneralBuildIdentityInformation(plist_t buildidentity);

char* extractPayloadFromIM4P(const char* buf, const char** compname, size_t *len);

#ifdef __cplusplus
}
#endif
    
#endif /* img4_h */