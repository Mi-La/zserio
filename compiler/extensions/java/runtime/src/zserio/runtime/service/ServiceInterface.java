package zserio.runtime.service;

import zserio.runtime.io.Writer;

/** Generic interface for all Zserio services on server side. */
public interface ServiceInterface
{
    /**
     * Calls method with the given name synchronously.
     *
     * @param <T> Zserio object type.
     * @param methodName Name of the service method to call.
     * @param requestData Request data to be passed to the method.
     * @param context Context specific for particular service.
     *
     * @return Response service data.
     */
    public <T extends Writer> ServiceData<T> callMethod(String methodName, byte[] requestData, Object context);
};
