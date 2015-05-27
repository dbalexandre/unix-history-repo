# $FreeBSD$
# Generated by h2py from stdin

# Included from sys/ioccom.h
IOCPARM_SHIFT = 13
IOCPARM_MASK = ((1 << IOCPARM_SHIFT) - 1)
def IOCPARM_LEN(x): return (((x) >> 16) & IOCPARM_MASK)

def IOCBASECMD(x): return ((x) & ~(IOCPARM_MASK << 16))

def IOCGROUP(x): return (((x) >> 8) & 0xff)

IOCPARM_MAX = (1 << IOCPARM_SHIFT)
IOC_VOID = 0x20000000
IOC_OUT = 0x40000000
IOC_IN = 0x80000000
IOC_INOUT = (IOC_IN|IOC_OUT)
IOC_DIRMASK = (IOC_VOID|IOC_OUT|IOC_IN)

# Included from sys/cdefs.h
def __has_feature(x): return 0

def __has_include(x): return 0

def __has_builtin(x): return 0

__GNUCLIKE_ASM = 3
__GNUCLIKE_ASM = 2
__GNUCLIKE___TYPEOF = 1
__GNUCLIKE___OFFSETOF = 1
__GNUCLIKE___SECTION = 1
__GNUCLIKE_CTOR_SECTION_HANDLING = 1
__GNUCLIKE_BUILTIN_CONSTANT_P = 1
__GNUCLIKE_BUILTIN_VARARGS = 1
__GNUCLIKE_BUILTIN_STDARG = 1
__GNUCLIKE_BUILTIN_VAALIST = 1
__GNUC_VA_LIST_COMPATIBILITY = 1
__GNUCLIKE_BUILTIN_NEXT_ARG = 1
__GNUCLIKE_BUILTIN_MEMCPY = 1
__CC_SUPPORTS_INLINE = 1
__CC_SUPPORTS___INLINE = 1
__CC_SUPPORTS___INLINE__ = 1
__CC_SUPPORTS___FUNC__ = 1
__CC_SUPPORTS_WARNING = 1
__CC_SUPPORTS_VARADIC_XXX = 1
__CC_SUPPORTS_DYNAMIC_ARRAY_INIT = 1
def __P(protos): return protos		 

def __STRING(x): return #x		 

def __XSTRING(x): return __STRING(x)	 

def __P(protos): return ()		 

def __STRING(x): return "x"

def __aligned(x): return __attribute__((__aligned__(x)))

def __section(x): return __attribute__((__section__(x)))

def __aligned(x): return __attribute__((__aligned__(x)))

def __section(x): return __attribute__((__section__(x)))

def _Alignas(x): return alignas(x)

def _Alignas(x): return __aligned(x)

def _Alignof(x): return alignof(x)

def _Alignof(x): return __alignof(x)

def __nonnull(x): return __attribute__((__nonnull__(x)))

def __predict_true(exp): return __builtin_expect((exp), 1)

def __predict_false(exp): return __builtin_expect((exp), 0)

def __predict_true(exp): return (exp)

def __predict_false(exp): return (exp)

def __format_arg(fmtarg): return __attribute__((__format_arg__ (fmtarg)))

def __GLOBL(sym): return __GLOBL1(sym)

def __FBSDID(s): return __IDSTRING(__CONCAT(__rcsid_,__LINE__),s)

def __RCSID(s): return __IDSTRING(__CONCAT(__rcsid_,__LINE__),s)

def __RCSID_SOURCE(s): return __IDSTRING(__CONCAT(__rcsid_source_,__LINE__),s)

def __SCCSID(s): return __IDSTRING(__CONCAT(__sccsid_,__LINE__),s)

def __COPYRIGHT(s): return __IDSTRING(__CONCAT(__copyright_,__LINE__),s)

_POSIX_C_SOURCE = 199009
_POSIX_C_SOURCE = 199209
__XSI_VISIBLE = 700
_POSIX_C_SOURCE = 200809
__XSI_VISIBLE = 600
_POSIX_C_SOURCE = 200112
__XSI_VISIBLE = 500
_POSIX_C_SOURCE = 199506
_POSIX_C_SOURCE = 198808
__POSIX_VISIBLE = 200809
__ISO_C_VISIBLE = 1999
__POSIX_VISIBLE = 200112
__ISO_C_VISIBLE = 1999
__POSIX_VISIBLE = 199506
__ISO_C_VISIBLE = 1990
__POSIX_VISIBLE = 199309
__ISO_C_VISIBLE = 1990
__POSIX_VISIBLE = 199209
__ISO_C_VISIBLE = 1990
__POSIX_VISIBLE = 199009
__ISO_C_VISIBLE = 1990
__POSIX_VISIBLE = 198808
__ISO_C_VISIBLE = 0
__POSIX_VISIBLE = 0
__XSI_VISIBLE = 0
__BSD_VISIBLE = 0
__ISO_C_VISIBLE = 1990
__POSIX_VISIBLE = 0
__XSI_VISIBLE = 0
__BSD_VISIBLE = 0
__ISO_C_VISIBLE = 1999
__POSIX_VISIBLE = 0
__XSI_VISIBLE = 0
__BSD_VISIBLE = 0
__ISO_C_VISIBLE = 2011
__POSIX_VISIBLE = 200809
__XSI_VISIBLE = 700
__BSD_VISIBLE = 1
__ISO_C_VISIBLE = 2011
__NO_TLS = 1
CRYPTO_DRIVERS_INITIAL = 4
CRYPTO_SW_SESSIONS = 32
NULL_HASH_LEN = 16
MD5_HASH_LEN = 16
SHA1_HASH_LEN = 20
RIPEMD160_HASH_LEN = 20
SHA2_256_HASH_LEN = 32
SHA2_384_HASH_LEN = 48
SHA2_512_HASH_LEN = 64
MD5_KPDK_HASH_LEN = 16
SHA1_KPDK_HASH_LEN = 20
HASH_MAX_LEN = SHA2_512_HASH_LEN
NULL_HMAC_BLOCK_LEN = 64
MD5_HMAC_BLOCK_LEN = 64
SHA1_HMAC_BLOCK_LEN = 64
RIPEMD160_HMAC_BLOCK_LEN = 64
SHA2_256_HMAC_BLOCK_LEN = 64
SHA2_384_HMAC_BLOCK_LEN = 128
SHA2_512_HMAC_BLOCK_LEN = 128
HMAC_MAX_BLOCK_LEN = SHA2_512_HMAC_BLOCK_LEN
HMAC_IPAD_VAL = 0x36
HMAC_OPAD_VAL = 0x5C
NULL_BLOCK_LEN = 4
DES_BLOCK_LEN = 8
DES3_BLOCK_LEN = 8
BLOWFISH_BLOCK_LEN = 8
SKIPJACK_BLOCK_LEN = 8
CAST128_BLOCK_LEN = 8
RIJNDAEL128_BLOCK_LEN = 16
AES_BLOCK_LEN = RIJNDAEL128_BLOCK_LEN
CAMELLIA_BLOCK_LEN = 16
EALG_MAX_BLOCK_LEN = AES_BLOCK_LEN
AALG_MAX_RESULT_LEN = 64
CRYPTO_ALGORITHM_MIN = 1
CRYPTO_DES_CBC = 1
CRYPTO_3DES_CBC = 2
CRYPTO_BLF_CBC = 3
CRYPTO_CAST_CBC = 4
CRYPTO_SKIPJACK_CBC = 5
CRYPTO_MD5_HMAC = 6
CRYPTO_SHA1_HMAC = 7
CRYPTO_RIPEMD160_HMAC = 8
CRYPTO_MD5_KPDK = 9
CRYPTO_SHA1_KPDK = 10
CRYPTO_RIJNDAEL128_CBC = 11
CRYPTO_AES_CBC = 11
CRYPTO_ARC4 = 12
CRYPTO_MD5 = 13
CRYPTO_SHA1 = 14
CRYPTO_NULL_HMAC = 15
CRYPTO_NULL_CBC = 16
CRYPTO_DEFLATE_COMP = 17
CRYPTO_SHA2_256_HMAC = 18
CRYPTO_SHA2_384_HMAC = 19
CRYPTO_SHA2_512_HMAC = 20
CRYPTO_CAMELLIA_CBC = 21
CRYPTO_AES_XTS = 22
CRYPTO_AES_ICM = 23
CRYPTO_AES_NIST_GMAC = 24
CRYPTO_AES_NIST_GCM_16 = 25
CRYPTO_AES_128_NIST_GMAC = 26
CRYPTO_AES_192_NIST_GMAC = 27
CRYPTO_AES_256_NIST_GMAC = 28
CRYPTO_ALGORITHM_MAX = 28
CRYPTO_ALG_FLAG_SUPPORTED = 0x01
CRYPTO_ALG_FLAG_RNG_ENABLE = 0x02
CRYPTO_ALG_FLAG_DSA_SHA = 0x04
CRYPTO_FLAG_HARDWARE = 0x01000000
CRYPTO_FLAG_SOFTWARE = 0x02000000
COP_ENCRYPT = 1
COP_DECRYPT = 2
COP_F_BATCH = 0x0008
CRK_MAXPARAM = 8
CRK_ALGORITM_MIN = 0
CRK_MOD_EXP = 0
CRK_MOD_EXP_CRT = 1
CRK_DSA_SIGN = 2
CRK_DSA_VERIFY = 3
CRK_DH_COMPUTE_KEY = 4
CRK_ALGORITHM_MAX = 4
CRF_MOD_EXP = (1 << CRK_MOD_EXP)
CRF_MOD_EXP_CRT = (1 << CRK_MOD_EXP_CRT)
CRF_DSA_SIGN = (1 << CRK_DSA_SIGN)
CRF_DSA_VERIFY = (1 << CRK_DSA_VERIFY)
CRF_DH_COMPUTE_KEY = (1 << CRK_DH_COMPUTE_KEY)
CRD_F_ENCRYPT = 0x01
CRD_F_IV_PRESENT = 0x02
CRD_F_IV_EXPLICIT = 0x04
CRD_F_DSA_SHA_NEEDED = 0x08
CRD_F_COMP = 0x0f
CRD_F_KEY_EXPLICIT = 0x10
CRYPTO_F_IMBUF = 0x0001
CRYPTO_F_IOV = 0x0002
CRYPTO_F_BATCH = 0x0008
CRYPTO_F_CBIMM = 0x0010
CRYPTO_F_DONE = 0x0020
CRYPTO_F_CBIFSYNC = 0x0040
CRYPTO_BUF_CONTIG = 0x0
CRYPTO_BUF_IOV = 0x1
CRYPTO_BUF_MBUF = 0x2
CRYPTO_OP_DECRYPT = 0x0
CRYPTO_OP_ENCRYPT = 0x1
CRYPTO_HINT_MORE = 0x1
def CRYPTO_SESID2HID(_sid): return (((_sid) >> 32) & 0x00ffffff)

def CRYPTO_SESID2CAPS(_sid): return (((_sid) >> 32) & 0xff000000)

def CRYPTO_SESID2LID(_sid): return (((u_int32_t) (_sid)) & 0xffffffff)

CRYPTOCAP_F_HARDWARE = CRYPTO_FLAG_HARDWARE
CRYPTOCAP_F_SOFTWARE = CRYPTO_FLAG_SOFTWARE
CRYPTOCAP_F_SYNC = 0x04000000
CRYPTO_SYMQ = 0x1
CRYPTO_ASYMQ = 0x2
