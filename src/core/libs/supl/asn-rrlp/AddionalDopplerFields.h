/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "RRLP-Components"
 * 	found in "../rrlp-components.asn"
 */

#ifndef _AddionalDopplerFields_H_
#define _AddionalDopplerFields_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* AddionalDopplerFields */
    typedef struct AddionalDopplerFields
    {
        long doppler1;
        long dopplerUncertainty;

        /* Context for parsing across buffer boundaries */
        asn_struct_ctx_t _asn_ctx;
    } AddionalDopplerFields_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_AddionalDopplerFields;

#ifdef __cplusplus
}
#endif

#endif /* _AddionalDopplerFields_H_ */
#include <asn_internal.h>
