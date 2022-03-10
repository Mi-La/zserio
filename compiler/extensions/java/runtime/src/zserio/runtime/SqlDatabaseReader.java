package zserio.runtime;

import java.sql.Connection;
import java.sql.SQLException;

/**
 * The interface for read only SQL database classes generated by Zserio.
 */
public interface SqlDatabaseReader extends AutoCloseable
{
    /**
     * Closes the database connection.
     * <p>
     * The database is closed only if this object has been created by constructor using database file name.</p>
     *
     * @throws SQLException If the connection cannot be closed.
     */
    @Override
    public void close() throws SQLException;

    /**
     * Gets the underlying database connection.
     *
     * @return The database connection.
     */
    public Connection connection();
}
