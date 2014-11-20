
#ifndef FE_H
#define FE_H

#define DATA_LINE_LENGTH 512

namespace fe {

/*
 * Datatypes
 */
typedef unsigned int	FEenum;
typedef bool			FEbool;
typedef unsigned int	FEbitfield;
typedef void		FEvoid;
typedef signed char	FEbyte;		/* 1-byte signed */
typedef short		FEshort;	/* 2-byte signed */
typedef int			FEint;		/* 4-byte signed */
typedef unsigned char	FEubyte;	/* 1-byte unsigned */
typedef unsigned short	FEushort;	/* 2-byte unsigned */
typedef unsigned int	FEuint;		/* 4-byte unsigned */
typedef int			FEsizei;	/* 4-byte signed */
typedef float		FEfloat;	/* single precision float */
typedef double		FEdouble;	/* double precision float */
typedef char		FEchar;

static const FEbool FEtrue = true;
static const FEbool FEfalse = false;

} //end namespace

#endif