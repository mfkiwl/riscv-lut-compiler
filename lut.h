#ifndef RISCV_LUT_COMPULER_LUT_H
#define RISCV_LUT_COMPULER_LUT_H

#include "error.h"
#include "keyvalue.h"
#include "segment.h"
#include "target-function.h"
#include "util.h"
#include "dlib.h"

#include <alpha/alpha.h>

/** represents a single Lookup table.
  *
  * Contains all the information obtained from Input or intermediate files
  * and generated afterwards.
  *
  * All keyvalues read from input files are stored but meaningful ones are
  * interpreted as well and stored in appropriate fields.
  */
class LookupTable {
  public:
    typedef void (*target_func_t)(seg_data_t *res, const seg_data_t *arg0);
  protected:
    
    /** Lookup table identifier generated *externally* and guaranteed to be 
      * unique among all Lookup tables used in a single program.
      */
    alp::string _ident;
    
    alp::string _target_name;
    target_type_t _target_result_type;
    alp::array_t<target_type_t> _target_argument_types;
    
    dynamic_library_t *_target_lib;
    target_func_t _target_func;

    alp::string _c_code;

    alp::array_t<KeyValue*> _keyvalues;
    target_function_t _target_function;

    alp::array_t<segment_t> _segments;

  public:
    /** Constructor.
      *
      * Creates an emtpy Lookup table.
      */
    LookupTable();

    ~LookupTable();
    
    /** Getter for this LUT's identifier */
    const alp::string &ident() const { return _ident;}
    
    /** Attempts to retrieve a named key-value.
      *
      * \param key Name of the keyvalue to retrieve.
      * \return index of the keyvalue or -1 if it was not found.
      */
    ssize_t findKeyValue(const alp::string &key) const;
    /** Attempts to retrieve a named key-value.
      *
      * \param key Name of the keyvalue to retrieve.
      * \return Pointer to the keyvalue if it exists, NULL otherwise.
      */
    KeyValue *getKeyValue(const alp::string &key) const;
    
    /** Parses an input format buffer and integrates its content into this
      * instance.
      * 
      * Any additional information that was read from previous calls to
      * parseInput, parseIntermediate or was otherwise generated will be lost.
      *
      * @param ptr Pointer into the beginning of the buffer to read from.
      * @param cb Length of the buffer starting at ptr, in bytes.
      * @param name Name used to identify the compilation unit in debug/error
      * output
      */
    void parseInput(const char *ptr, size_t cb, const char *name=NULL);

    /** Parses an input format file using parseInput.
      *
      * @param fn File name of the file to be read
      * @throw FileIOException The given file could not be read.
      */
    void parseInputFile(const char *fn);
    
    
    /** Parses a buffer expected to be in intermediate representation.
      * 
      * Any additional information that was read from previous calls to
      * parseInput, parseIntermediate or was otherwise generated will be lost.
      *
      * @param ptr Pointer into the beginning of the buffer to read from.
      * @param cb Length of the buffer starting at ptr, in bytes.
      */
    void parseIntermediate(const char *ptr, size_t cb, const char *name=NULL);

    /** Parses an intermediate format file using parseIntermediate.
      *
      * @param fn File name of the file to be read
      * @throw FileIOException The given file could not be read.
      * @param name Name used to identify the compilation unit in debug/error
      * output
      */
    void parseIntermediateFile(const char *fn);
    
    /** Generates a representation of the Lookup table in intermediate
      * format.
      *
      * The result is a null-terminated string in intermediate format.
      *
      * @param pptr Pointer to a char pointer receiving the generated
      * buffer.
      * @param pcb Pointer to a size_t variable receiving the length of the
      * buffer. This does *not* include the terminating null character.
      */
    void generateIntermediateFormat(alp::string &res);
    /** Writes a representation of this Lookup table to an intermediate file.
      *
      * \param fn File name to write to
      * \throw FileIOException The file could not be written to.
      * \see generateIntermediateFormat
      */
    void saveIntermediateFile(const char *fn);
    
    
    /** Generates a representation of the Lookup table in final output format.
      *
      * Outputs an assembly code file specifying a static constant data (bss)
      * segment with a label for this Lookup table's identifier.
      */
    void generateOutputFormat(char **pptr, size_t *pcb);

    /** Saves the final assembly code output to a file.
      *
      * \param fn File name to write to
      * \throw FileIOException The file could not be written to.
      */
    void saveOutputFile(const char *fn);
    
    /** Adds a new segment into the LUT.
      *
      * \param seg Segment to insert.
      * \param correctOverlap Set to true to adjust other segments to
      * keep the set of segments disjoint. Otherwise it is expected not to
      * overlap with any other segment.
      * \throw RuntimeError The given segment overlaps with another segment
      * and correctOverlap was set to false.
      */
    void addSegment(const segment_t &seg, bool correctOverlap);

    void evaluate(const seg_data_t &arg, seg_data_t &res);
    seg_data_t evaluate(const seg_data_t &arg);


};

#endif
