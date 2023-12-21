#ifndef ZSERIO_ISERVICE_H_INC
#define ZSERIO_ISERVICE_H_INC

#include "zserio/IReflectable.h"
#include "zserio/Span.h"
#include "zserio/StringView.h"
#include "zserio/Types.h"
#include "zserio/Vector.h"

namespace zserio
{

/**
 * Service data interface.
 *
 * When reflectable interface is available, holds the reflectable object, otherwise holds the serialized data.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class IBasicServiceData
{
public:
    /** Destructor. */
    virtual ~IBasicServiceData() = default;

    /**
     * Gets reflectable representing the service data (if available).
     *
     * \return Reflectable or null when no reflectable is available.
     */
    virtual IBasicReflectableConstPtr<ALLOC> getReflectable() const = 0;

    /**
     * Gets service data as bytes.
     *
     * \return Service data.
     */
    virtual Span<const uint8_t> getData() const = 0;
};

/** Typedef to service data smart pointer needed for convenience in generated code. */
template <typename ALLOC = std::allocator<uint8_t>>
using IBasicServiceDataPtr = std::shared_ptr<IBasicServiceData<ALLOC>>;

/**
 * Service data implementation based on reflectable interface.
 *
 * Holds reference to the reflectable object and lazy-initialized serialized data in case that
 * getData() is used.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class BasicReflectableServiceData : public IBasicServiceData<ALLOC>
{
public:
    /**
     * Constructor from reflectable.
     *
     * \param reflectable Constant reflectable created from zserio request object.
     * \param allocator Allocator to use for data allocation.
     */
    explicit BasicReflectableServiceData(
            const IBasicReflectableConstPtr<ALLOC>& reflectable, const ALLOC& allocator = ALLOC()) :
            m_reflectable(reflectable),
            m_data(allocator)
    {}

    IBasicReflectableConstPtr<ALLOC> getReflectable() const override
    {
        return m_reflectable;
    }

    /**
     * Lazy initialized data serialized using the reflectable object.
     *
     * \copydoc IBasicServiceData::getData()
     */
    Span<const uint8_t> getData() const override
    {
        if (m_reflectable && m_data.getBitSize() == 0)
        {
            // lazy initialization
            m_data = BasicBitBuffer<ALLOC>(m_reflectable->bitSizeOf(), m_data.get_allocator());
            BitStreamWriter writer(m_data);
            m_reflectable->write(writer);
        }
        return m_data.getData();
    }

private:
    IBasicReflectableConstPtr<ALLOC> m_reflectable;
    mutable BasicBitBuffer<ALLOC> m_data;
};

/**
 * Service data implementation based on objects generated by Zserio.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class BasicObjectServiceData : public IBasicServiceData<ALLOC>
{
public:
    /**
     * Constructor from zserio-generated object.
     *
     * \param object Reference to zserio object.
     * \param allocator Allocator to use for data allocation
     */
    template <typename ZSERIO_OBJECT>
    explicit BasicObjectServiceData(ZSERIO_OBJECT& object, const ALLOC& allocator = ALLOC()) :
            m_data(object.bitSizeOf(), allocator)
    {
        BitStreamWriter writer(m_data);
        object.write(writer);
    }

    IBasicReflectableConstPtr<ALLOC> getReflectable() const override
    {
        return nullptr;
    }

    Span<const uint8_t> getData() const override
    {
        return m_data.getData();
    }

private:
    BasicBitBuffer<ALLOC> m_data;
};

/**
 * Service data implementation which owns the data.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class BasicRawServiceDataHolder : public IBasicServiceData<ALLOC>
{
public:
    /**
     * Constructor from vector const l-value reference.
     *
     * \param rawData Raw data to be copied inside the service data.
     */
    explicit BasicRawServiceDataHolder(const vector<uint8_t, ALLOC>& rawData) :
            m_data(rawData)
    {}

    /**
     * Constructor from vector r-value reference.
     *
     * \param rawData Raw data to be moved inside the service data.
     */
    explicit BasicRawServiceDataHolder(vector<uint8_t, ALLOC>&& rawData) :
            m_data(std::move(rawData))
    {}

    IBasicReflectableConstPtr<ALLOC> getReflectable() const override
    {
        return nullptr;
    }

    Span<const uint8_t> getData() const override
    {
        return m_data;
    }

private:
    vector<uint8_t, ALLOC> m_data;
};

/**
 * Service data implementation which only keeps pointer to the raw data buffer.
 *
 * Must be used with caution only when the proper life-time of the data is ensured.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class BasicRawServiceDataView : public IBasicServiceData<ALLOC>
{
public:
    /**
     * Constructor from span.
     *
     * \param rawData Span as a pointer to the raw data buffer.
     */
    explicit BasicRawServiceDataView(zserio::Span<const uint8_t> rawData) :
            m_data(rawData)
    {}

    IBasicReflectableConstPtr<ALLOC> getReflectable() const override
    {
        return nullptr;
    }

    Span<const uint8_t> getData() const override
    {
        return m_data;
    }

private:
    Span<const uint8_t> m_data;
};

/**
 * Generic interface for all Zserio services to be used on the server side.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class IBasicService
{
public:
    virtual ~IBasicService() = default;

    /**
     * Calls method with the given name synchronously.
     *
     * \param methodName Name of the service method to call.
     * \param requestData Request data to be passed to the method.
     * \param context Context specific for particular service or nullptr in case of no context.
     *
     * \return Created response data.
     *
     * \throw ServiceException if the call fails.
     */
    virtual IBasicServiceDataPtr<ALLOC> callMethod(
            StringView methodName, Span<const uint8_t> requestData, void* context) = 0;
};

/**
 * Generic interface for all Zserio services to be used on the client side.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class IBasicServiceClient
{
public:
    virtual ~IBasicServiceClient() = default;

    /**
     * Calls method with the given name synchronously.
     *
     * \param methodName Name of the service method to call.
     * \param requestData Request data to be passed to the method.
     * \param context Context specific for particular service or nullptr in case of no context.
     *
     * \return Created response data as bytes.
     *
     * \throw ServiceException if the call fails.
     */
    virtual vector<uint8_t, ALLOC> callMethod(
            StringView methodName, const IBasicServiceData<ALLOC>& requestData, void* context) = 0;
};

/** Typedef to service interface provided for convenience - using default std::allocator<uint8_t>. */
/** \{ */
using IServiceData = IBasicServiceData<>;
using IServiceDataPtr = IBasicServiceDataPtr<>;
using IService = IBasicService<>;
using IServiceClient = IBasicServiceClient<>;
/** \} */

/** Typedef to service data implementation provided for convenience - using default std::allocator<uint8_t>. */
/** \{ */
using ReflectableServiceData = BasicReflectableServiceData<>;
using ObjectServiceData = BasicObjectServiceData<>;
using RawServiceDataHolder = BasicRawServiceDataHolder<>;
using RawServiceDataView = BasicRawServiceDataView<>;
/** \} */

} // namespace zserio

#endif // ifndef ZSERIO_ISERVICE_H_INC
