<#include "FileHeader.inc.ftl"/>
<#include "CompoundConstructor.inc.ftl"/>
<#include "CompoundField.inc.ftl"/>
<#include "CompoundFunction.inc.ftl"/>
<#include "CompoundParameter.inc.ftl"/>
<@file_header generatorDescription/>

<@all_imports packageImports typeImports/>

<#assign hasFieldWithConstraint=false/>
<#list fieldList as field>
    <#if field.constraint??>
        <#assign hasFieldWithConstraint=true/>
        <#break>
    </#if>
</#list>
class ${name}():
    <@compound_constructors compoundConstructorsData/>

<#if withWriterCode && fieldList?has_content>
    <#assign constructorParamList><@compound_constructor_parameters compoundParametersData/></#assign>
    @classmethod
    def fromFields(cls<#if constructorParamList?has_content>, ${constructorParamList}</#if><#rt>
                   <#lt><#list fieldList as field>, <@field_argument_name field/></#list>)
        instance = cls(${constructorParamList})
    <#list fieldList as field>
        instance.<@field_member_name field/> = <@field_argument_name field/>
    </#list>

        return instance

</#if>
    def __eq__(self, other):
        return (<@compound_compare_parameters compoundParametersData, 4/><#if fieldList?has_content> and</#if>
<#list fieldList as field>
                <@compound_compare_field field, 4/><#if field_has_next> and<#else>)</#if>
</#list>

    def __hash__(self):
        result = zserio.hashcode.HASH_SEED
        <@compound_hashcode_parameters compoundParametersData/>
<#list fieldList as field>
        <@compound_hashcode_field field/>
</#list>

        return result

    def bitSizeOf(self, bitPosition=0):
        endBitPosition = bitPosition
<#list fieldList as field>
        <@compound_bitsizeof_field field/>
</#list>

        return endBitPosition - bitPosition

<#if withWriterCode>
    def initializeOffsets(self, bitPosition):
    <#if hasFieldWithOffset>
        endBitPosition = bitPosition
        <#list fieldList as field>
        <@compound_initialize_offsets_field field/>
        </#list>

        return endBitPosition
    <#else>
        return bitPosition + self.bitSizeOf(bitPosition)
    </#if>

</#if>
    <@compound_parameter_accessors compoundParametersData/>
<#list fieldList as field>
    def ${field.getterName}(self):
        return self.<@field_member_name field/><#if field.array??>.getRawArray()</#if>

    <#if withWriterCode>
    def ${field.setterName}(self, <@field_argument_name field/>):
<#--  TODO range check is missing      <@range_check field.rangeCheckData, name/> -->
        <#if field.array??>
        self.<@field_member_name field/> = zserio.Array(${field.array.traitsName}(<#-- TODO -->), <@field_argument_name field/><#rt>
            <#lt><#if field.array.isImplicit>, isImplicit=True<#rt>
            <#lt><#elseif !field.array.length??>, isAuto=True</#if><#rt>
            <#if field.offset?? && field.offset.containsIndex>
                <#lt>, setOffsetMethod=None, checkOffsetMethod=None<#rt>  <#-- TODO -->
            </#if>
            <#lt>)
        <#else>
        self.<@field_member_name field/> = <@field_argument_name field/>
        </#if>

    </#if>
    <#if field.optional??>
    def ${field.optional.indicatorName}(self):
        return (<#if field.optional.clause??>${field.optional.clause}<#else>${field.getterName}() != None</#if>)

    </#if>
</#list>
    def read(self, reader):
<#list fieldList as field>
    <@compound_read_field field, name/>
    <#if field_has_next>

    </#if>
</#list>
    <#if hasFieldWithConstraint>

        <#--  TODO check constraints is missing -->
    </#if>
<#if withWriterCode>

    def write(self, writer, callInitializeOffsets=None):
    <#if hasFieldWithOffset>
    startBitPosition = writer.getBitPosition()
    if callInitializeOffsets:
        initializeOffsets(startBitPosition)
    </#if>
    <#if hasFieldWithConstraint>

        <#--  TODO check constraints is missing -->
    </#if>
    <#list fieldList as field>
    <@compound_write_field field, name/>
        <#if field_has_next>

        </#if>
    </#list>
</#if>
