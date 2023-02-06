#pragma once
#include "Toucan.h"

namespace Toucan
{
/**
 * @brief Shader data types
 */
enum class BufferElementType : uint8
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Mat3,
    Mat4,
    Bool
};

static uint32 GetElementSize(const BufferElementType &Type)
{
    switch (Type)
    {
    case BufferElementType::Float:
        return 4;
    case BufferElementType::Float2:
        return 4 * 2;
    case BufferElementType::Float3:
        return 4 * 3;
    case BufferElementType::Float4:
        return 4 * 4;
    case BufferElementType::Mat3:
        return 4 * 3 * 3;
    case BufferElementType::Mat4:
        return 4 * 4 * 4;
    case BufferElementType::Int:
        return 4;
    case BufferElementType::Int2:
        return 4 * 2;
    case BufferElementType::Int3:
        return 4 * 3;
    case BufferElementType::Int4:
        return 4 * 4;
    case BufferElementType::Bool:
        return 1;
    default:
        return 0;
    }
}

struct BufferElement
{
    String Name;
    uint32 Offset;
    uint32 Size;
    BufferElementType ElementType;
    bool IsNormalized;

  public:
    BufferElement(BufferElementType _Type, String _Name, bool _IsNormalized = false)
        : ElementType(_Type), Name(_Name), IsNormalized(_IsNormalized), Size(GetElementSize(_Type)), Offset(0)
    {
    }
};

/** Buffer layout */
class BufferLayout
{
    Array<BufferElement> m_BufferElements;
    uint32 m_Stride;

  public:
    BufferLayout(const std::initializer_list<BufferElement> &BufferElements)
        : m_BufferElements(BufferElements), m_Stride(0)
    {
        CalculateElementsOffsetAndStride();
    }

    const Array<BufferElement> &GetElements() const { return m_BufferElements; }

  private:
    void CalculateElementsOffsetAndStride()
    {
        uint32 currentOffset = 0;
        for (BufferElement &element : m_BufferElements)
        {
            element.Offset = currentOffset;
            currentOffset += element.Size;
        }
        m_Stride = currentOffset;
    }
};

class Buffer
{
  protected:
    BufferLayout m_Layout;
    uint32 m_Size;

  public:
    Buffer() : m_Layout({}), m_Size(0) {}

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    /**
     * @brief Get the Layout descriptor object of this buffer.
     * @return const BufferLayout& - Layout descriptor of this buffer.
     */
    virtual const BufferLayout &GetLayout() { return m_Layout; }

    /**
     * @brief Set buffer elements layout.
     * @param Layout Layout descriptor of this buffer.
     */
    virtual void SetLayout(const BufferLayout &Layout) { m_Layout = Layout; };

    /** Get buffer total size in bytes. */
    virtual uint32 GetSize() { return m_Size; };

    /**
     * @brief Set buffer data
     * @param Data Pointer to the data to be set.
     * @param Size Size in bytes of the data to be set.
     */
    virtual void SetData(void *Data, uint32 Size) = 0;
};

class VertexBuffer : public Buffer
{
  public:
    /**
     * @brief Create a vertex buffer for the current active renderer.
     * @param Vertices Pointer to vertex array data.
     * @param Size Size in bytes of the vertex array.
     * @return Reference to the created VertexBuffer.
     */
    static Ref<VertexBuffer> Create(void *Vertices, uint32 Size, const BufferLayout &Layout);
};

class IndexBuffer : public Buffer
{
  public:
    /**
     * @brief Create a index buffer for the current active renderer.
     * @param Indexes Pointer to the index array data.
     * @param Count Number of elements in the index array.
     * @return Reference to the created IndexBuffer.
     */
    static Ref<IndexBuffer> Create(void *Indexes, uint32 Count);
};

} // namespace Toucan