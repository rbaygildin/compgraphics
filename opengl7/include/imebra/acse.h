/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file acse.h
    \brief Declaration of the the ACSE classes.
*/

#if !defined(imebraACSE__INCLUDED_)
#define imebraACSE__INCLUDED_

#ifndef SWIG

#include <memory>
#include <vector>
#include <string>
#include "definitions.h"

namespace imebra
{

namespace implementation
{
    class associationBase;
    class associationBase;
    class associationMessage;
    class presentationContext;
    class presentationContexts;
}

}

#endif

namespace imebra
{

class StreamReader;
class StreamWriter;
class DataSet;

///
/// \brief A presentation context defines which transfer syntaxes are supported
///        for a specific abstract syntax.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API PresentationContext
{
    PresentationContext(const PresentationContext&) = delete;
    PresentationContext& operator=(const PresentationContext&) = delete;

#ifndef SWIG
    friend class PresentationContexts;

#endif

public:
    ///
    /// \brief Constructor.
    ///
    /// The SCU will act as SCU and the SCP will act as SCP when using this
    /// presentation context. To specify the roles of the SCU and the SCP
    /// use the other constructor which includes the roles parameters.
    ///
    /// \param abstractSyntax the abstract syntax described by this presentation
    ///                       context
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit PresentationContext(const std::string& abstractSyntax);

    ///
    /// \brief Constructor.
    ///
    /// \param abstractSyntax the abstract syntax described by this presentation
    ///                       context
    /// \param bSCURole       if true then the SCU will act as an SCU.
    ///                       The SCU and SCP can be both an SCU and an SCP for
    ///                       the same abstract syntax
    /// \param bSCPRole       if true then the SCU will act as an SCP
    ///                       The SCU and SCP can be both an SCU and an SCP for
    ///                       the same abstract syntax
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit PresentationContext(const std::string& abstractSyntax, bool bSCURole, bool bSCPRole);

    ///
    /// \brief Add a supported transfer syntax to the presentation context.
    ///
    /// \param transferSyntax the transfer syntax to add
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void addTransferSyntax(const std::string& transferSyntax);

    virtual ~PresentationContext();

#ifndef SWIG
protected:
    std::shared_ptr<implementation::presentationContext> m_pPresentationContext;
#endif

};


///
/// \brief A collection of presentation contexts.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API PresentationContexts
{
    PresentationContexts(const PresentationContext&) = delete;
    PresentationContexts& operator=(const PresentationContext&) = delete;

#ifndef SWIG
    friend class AssociationSCU;
    friend class AssociationSCP;
#endif
public:
    PresentationContexts();
    virtual ~PresentationContexts();

    ///
    /// \brief Add a presentation context to the collection.
    ///
    /// \param presentationContext the presentation context to add to the
    ///                            collection
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void addPresentationContext(const PresentationContext& presentationContext);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::presentationContexts> m_pPresentationContexts;
#endif
};


///
/// \brief A message composed by one or two datasets.
///
/// When sending a message through an AssociationBase derived object then
/// up to two dataset can be included into the message: the first dataset is
/// be the command dataset, while the optional second one is the
/// command's payload.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API AssociationMessage
{
    AssociationMessage(const AssociationMessage&) = delete;
    AssociationMessage& operator=(const AssociationMessage&) = delete;

#ifndef SWIG
    friend class AssociationBase;
    friend class DimseService;
    friend class DimseCommand;
    friend class DimseResponse;
protected:
    AssociationMessage();
    AssociationMessage(std::shared_ptr<implementation::associationMessage> pMessage);
#endif

public:
    ///
    /// \brief Constructor.
    ///
    /// \param abstractSyntax the abstract syntax of the message.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    AssociationMessage(const std::string& abstractSyntax);

    ///
    /// \brief Retrieve the message's abstract syntax
    ///
    /// \return the message's abstract syntax
    ///
    ///////////////////////////////////////////////////////////////////////////////
    std::string getAbstractSyntax() const;

    ///
    /// \brief Return the command stored in the message.
    ///
    /// \return the command DataSet
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSet* getCommand() const;

    ///
    /// \brief Return the payload stored in the message.
    ///
    /// \return the payload DataSet
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSet* getPayload() const;

    ///
    /// \brief Return true if the message has a payload.
    ///
    /// \return true if the message has a payload, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool hasPayload() const;

    ///
    /// \brief Add a command DataSet to the message.
    ///
    /// Two datasets can be transmitted at once: the first DataSet is the
    /// DICOM command, while the second optional one is the command payload.
    ///
    /// \param dataSet a DataSet to add to the message
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void addDataSet(const DataSet& dataSet);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::associationMessage> m_pMessage;
#endif

};


///
/// \brief The AssociationBase class
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API AssociationBase
{
    AssociationBase(const AssociationBase&) = delete;
    AssociationBase& operator=(const AssociationBase&) = delete;

#ifndef SWIG
    friend class DimseService;
#endif

protected:
    AssociationBase();

public:
    ///
    /// \brief Destructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~AssociationBase();

    ///
    /// \brief Read a command dataset and its payload (if any).
    ///
    /// Throws StreamClosedError if the association has been released or aborted.
    ///
    /// \return an AssociationDataSet containing a command and its payload.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    AssociationMessage* getCommand();

    ///
    /// \brief Read a response dataset and its payload (if any).
    ///
    /// Throws StreamClosedError if the association has been released or aborted.
    ///
    /// \return an AssociationDataSet containing a response and its payload.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    AssociationMessage* getResponse(std::uint16_t messageId);

    ///
    /// \brief Send a DICOM message to the connected peer.
    ///
    /// \param messageDataSet the DICOM message to send
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void sendMessage(const AssociationMessage& messageDataSet);

    ///
    /// \brief Releases the association.
    ///
    /// The method blocks until the other party acknowledges the release command
    /// or until the ACSE timout expires.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void release();

    ///
    /// \brief Aborts the association.
    ///
    /// The association will be aborted as soon as possible. The other party
    /// will not acknowledge the abort command.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void abort();

    ///
    /// \brief Returns our AET.
    ///
    /// \return our AET
    ///
    //////////////////////////////////////////////////////////////////
    std::string getThisAET() const;

    ///
    /// \brief Returns the other party's AET.
    ///
    /// \return the connected peer's AET
    ///
    //////////////////////////////////////////////////////////////////
    std::string getOtherAET() const;

    ///
    /// \brief Returns the transfer syntax negotiated for a specific
    ///        abstract syntax.
    ///
    /// Throws:
    /// - AcseNoTransferSyntaxError if no transfer syntax
    ///   is available for the requested abstract syntax or
    /// - AcsePresentationContextNotRequestedError if the abstract
    ///   syntax was not negotiated at all.
    ///
    /// \param abstractSyntax the abstract syntax for which the
    ///                       transfer syntax is requested
    /// \return the negotiated transfer syntax for the specified
    ///         abstract syntax
    ///
    //////////////////////////////////////////////////////////////////
    std::string getTransferSyntax(const std::string& abstractSyntax) const;

#ifndef SWIG
protected:
    std::shared_ptr<implementation::associationBase> m_pAssociation;
#endif
};


///
/// \brief Represents the SCU part of an association.
///
/// The constructor tries to create an association with an SCP via the
/// StreamReader and the StreamWriter passed as parameter; when communicating
/// through the TCPStream then the same object is used as reader and writer.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API AssociationSCU: public AssociationBase
{
    AssociationSCU(const AssociationSCU&) = delete;
    AssociationSCU& operator=(const AssociationSCU&) = delete;

public:
    ///
    /// \brief Initiates an association request.
    ///
    /// Blocks until the association has been negotiated successfully or an
    /// error occurs (an exception is thrown).
    ///
    /// \param thisAET              the AET of the SCU
    /// \param otherAET             the AET of the SCP with wich the association
    ///                             is negotiated
    /// \param invokedOperations    maximum number of parallel operations we
    ///                             intend to invoke when acting as a SCU
    /// \param performedOperations  maximum number of parallel operations we can
    ///                             perform when acting as a SCP
    /// \param presentationContexts list of proposed presentation contexts
    /// \param pInput               input stream from which the SCP receives
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param pOutput              output stream into which the SCP writes
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param dimseTimeoutSeconds  DIMSE timeout, in seconds. 0 means infinite
    ///
    /// The constructor blocks until an association has been successfully
    /// negotiated or until an error happens (an exception is thrown).
    ///
    /// Throws:
    /// - CorruptedAcseMessageError
    /// - AcseSCUApplicationContextNameNotSupportedError
    /// - AcseSCUCalledAETNotRecognizedError
    /// - CodecWrongFormatError
    /// - DicomCodecDepthLimitReachedError
    ///
    ///////////////////////////////////////////////////////////////////////////////
    AssociationSCU(
            const std::string& thisAET,
            const std::string& otherAET,
            std::uint32_t invokedOperations,
            std::uint32_t performedOperations,
            const PresentationContexts& presentationContexts,
            StreamReader& pInput,
            StreamWriter& pOutput,
            std::uint32_t dimseTimeoutSeconds);
};


///
/// \brief Represents the SCP part of an association.
///
/// The constructor waits for an incoming DICOM association request
/// (a-request-rq) and then returns once the association has been established,
/// or throws CorruptedAcseMessageError if the SCU sends a wrong message type.
///
/// <b>AssociationSCP lifecycle</b>
///
/// Only create an AssociationSCP object AFTER the StreamReader and
/// StreamWriter parameters have been successfully connected to their peer,
/// then keep it alive and poll the data via readCommand() and readPayload()
/// until a StreamClosedError or a CorruptedAcseMessageError are thrown.
///
/// StreamClosedError means that the association has been released or
/// aborted.
///
/// If you call the abort() method on the AssociationSCP you should still
/// wait for the StreamClosedError exception to be thrown by readCommand()
/// or readPayload().
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API AssociationSCP: public AssociationBase
{
    AssociationSCP(const AssociationSCP&) = delete;
    AssociationSCP& operator=(const AssociationSCP&) = delete;

public:
    ///
    /// \brief Listens for an association request.
    ///
    /// Blocks until the association has been negotiated successfully or an
    /// error occurs (an exception is thrown).
    ///
    /// \param thisAET              the AET of the SCP. If empty then the SCP
    ///                             will accept associations for any called AET,
    ///                             otherwise it will reject the association
    ///                             when the called AET does not match this one
    /// \param invokedOperations    maximum number of parallel operations we
    ///                             intend to invoke when acting as a SCU
    /// \param performedOperations  maximum number of parallel operations we can
    ///                             perform when acting as a SCP
    /// \param presentationContexts list of accepted presentation contexts
    /// \param pInput               input stream from which the SCP receives
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param pOutput              output stream into which the SCP writes
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param dimseTimeoutSeconds  DIMSE timeout, in seconds. 0 means infinite
    /// \param artimTimeoutSeconds  ARTIM timeout, in seconds. Amount of time that
    ///                             is allowed to pass before an association
    ///                             request arrives
    ///
    /// The constructor blocks until an association has been successfully
    /// negotiated or until an error happens (an exception is thrown).
    ///
    /// Throws:
    /// - CorruptedAcseMessageError
    /// - AcseSCUApplicationContextNameNotSupportedError
    /// - AcseSCUCalledAETNotRecognizedError
    /// - CodecWrongFormatError
    /// - DicomCodecDepthLimitReachedError
    ///
    ///////////////////////////////////////////////////////////////////////////////
    AssociationSCP(
            const std::string& thisAET,
            std::uint32_t invokedOperations,
            std::uint32_t performedOperations,
            const PresentationContexts& presentationContexts,
            StreamReader& pInput,
            StreamWriter& pOutput,
            std::uint32_t dimseTimeoutSeconds,
            std::uint32_t artimTimeoutSeconds);
};

}

#endif // !defined(imebraACSE__INCLUDED_)
