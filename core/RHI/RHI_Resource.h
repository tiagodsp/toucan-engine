
namespace Toucan
{

class IRHI_Resource
{
  public:
    IRHI_Resource(void *RHI_ResourceHandle) : m_RHI_ResourceHandle(RHI_ResourceHandle){};
    virtual void *GetRHIResourceHandle() const { return m_RHI_ResourceHandle; };

  protected:
    void *m_RHI_ResourceHandle;
};

} // namespace Toucan