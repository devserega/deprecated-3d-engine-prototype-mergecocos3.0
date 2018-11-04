#ifndef BUNDLE_H_
#define BUNDLE_H_

#include "cocos2d.h"

namespace cocos3d
{
class C3DScene;
class C3DNode;
class C3DModel;
class C3DLight;
class C3DMeshSkin;
class C3DMesh;

class C3DBone;
class C3DAnimation;

class BonePartData;
class MeshSkinData;
class MeshPartData;
class MeshData;

class C3DTransform;

class C3DMorph;

class C3DCamera;
class C3DStream;

/**
 * Represents a cocos3d bundle file (.ckb) that contains a
 * collection of binary game assets that can be loaded.
 */

class C3DStaticObj;
class C3DRenderNode;
class C3DSprite;
class C3DResourceLoader : public cocos2d::CCObject
{
friend class C3DRenderNode;
friend class C3DRenderNodeManager;

public:

    /**
     * Returns a C3DResourceLoader for the given resource path.
     */
    static C3DResourceLoader* create(const std::string& path);

	/**
     * load 3D sprite.
     */
	void loadSuperModel(C3DSprite* superModel);
	void reLoadSuperModel(C3DRenderNode* superModel);

	/**
     * load 3D static object.
     */
	void loadSceneModel(C3DStaticObj* sceneModel);

	//....load start....
	void loadSkeleton(C3DSprite* superModel,std::string baseBoneName);
	bool loadAnimation(C3DSprite* superModel);
	void loadSuperModel(C3DSprite* superModel,std::list<std::string>* models);
	void loadSuperModel(C3DSprite* superModel,std::string nodeName);
	//....load end....
    /**
     * Determines if this bundle contains a top-level object with the given ID.
     *
     * This method performs a case-sensitive comparison.
     *
     * @param id The ID of the object to search for.
     */
    bool contains(const std::string& id) const;

    /**
     * Returns the number of top-level objects in this bundle.
     */
    unsigned int getObjectCount() const;

    /**
     * Returns the unique identifier of the top-level object at the specified index in this bundle.
     *
     * @param index The index of the object.
     *
     * @return The ID of the object at the given index, or NULL if index is invalid.
     */
    const std::string getObjectID(unsigned int index) const;

	unsigned int seekToNextType();

	std::string getFilePath() const { return _path; }
private:

    class Reference
    {
    public:
        std::string id;
        unsigned int type;
        unsigned int offset;

        Reference();

        ~Reference();
    };

	/**
     * Constructor & Destructor.
     */
    C3DResourceLoader(const std::string& path);
    ~C3DResourceLoader();

    /**
     * Finds a reference by ID.
     */
    Reference* find(const std::string& id) const;

    /**
     * Resets any load session specific state for the bundle.
     */
    void clearLoadSession();

    /**
     * Returns the ID of the object at the current file position.
     * Returns NULL if not found.
     *
     * @return The ID string or NULL if not found.
     */
    const std::string getIdFromOffset() const;

    /**
     * Returns the ID of the object at the given file offset by searching through the reference table.
     * Returns NULL if not found.
     *
     * @param offset The file offset.
     *
     * @return The ID string or NULL if not found.
     */
    const std::string getIdFromOffset(unsigned int offset) const;

    /**
     * Seeks the file pointer to the object with the given ID and type
     * and returns the relevant Reference.
     *
     * @param id The ID string to search for.
     * @param type The object type.
     *
     * @return The reference object or NULL if there was an error.
     */
    Reference* seekTo(const std::string& id, unsigned int type);

    /**
     * Seeks the file pointer to the first object that matches the given type.
     *
     * @param type The object type.
     *
     * @return The reference object or NULL if there was an error.
     */
    Reference* seekToFirstType(unsigned int type);

    /**
     * Internal method to load a node.
     *
     * Only one of node or scene should be passed as non-NULL (or neither).
     */
	C3DNode* loadNode(const std::string& id, C3DSprite* superModelContext);
    /**
     * Loads a mesh with the specified ID from the bundle.
     *
     * @param id The ID of the mesh to load.
     * @param nodeId The id of the mesh's model's parent node.
     *
     * @return The loaded mesh, or NULL if the mesh could not be loaded.
     */
    C3DMesh* loadMesh(const std::string& nodeId, bool hasMorph);

    /**
     * Reads an xref string from the current file position.
     *
     * @param id The string to load the ID string into.
     *
     * @return True if successful, false if an error occurred.
     */
    bool readXref(std::string& id);

    /**
     * Recursively reads nodes from the current file position.
     * This method will load cameras, lights and models in the nodes.
     *
     * @return A pointer to new node or NULL if there was an error.
     */
	C3DNode* readNode(C3DRenderNode* compoundModelContext);
	bool reloadNode(C3DNode* context);

    /**
     * Reads a camera from the current file position.
     *
     * @return A pointer to a new camera or NULL if there was an error.
     */
    void readCamera(C3DCamera* camera);

    /**
     * Reads a light from the current file position.
     *
     * @return A pointer to a new light or NULL if there was an error.
     */
    void readLight(C3DLight* light);

    /**
     * Reads a model from the current file position.
     *
     * @return A pointer to a new model or NULL if there was an error.
     */
    C3DModel* readModel(const std::string& nodeId);

    /**
     * Reads mesh data from the current file position.
     */
    MeshData* readMeshData();

    /**
     * Reads a mesh skin from the current file position.
     *
     * @return A pointer to a new mesh skin or NULL if there was an error.
     */
    C3DMeshSkin* readMeshSkin();

	/**
     * read mesh morph.
     */
	C3DMorph* readMeshMorph();

    /**
     * Sets the transformation matrix.
     *
     * @param values A pointer to array of 16 floats.
     * @param transform The transform to set the values in.
     */
    void setTransform(const float* values, C3DTransform* transform);

    /**
     * Resolves joint references for all pending mesh skins.
     */
	void resolveJointReferences(C3DSprite* superModelContext);

	/**
     * read animation data.
     */
    void readAnimationChannelData(C3DAnimation* animation, const std::string& id, C3DBone* bone);
    void readAnimationChannel(C3DSprite* superModel, C3DAnimation* animation, const std::string& animationId);

    void readAnimation(C3DSprite* superModel);
    void readAnimations(C3DSprite* superModel);

    /**
     * load animation curves from file
     * return true if load sucess or already loaded
     */
    bool readAnimationCurves();
    bool isAnimationLoaded() const;
    bool loadAnimation2(C3DSprite* superModel);

private:

	//properties
    std::string _path;
    unsigned int _referenceCount;
    Reference* _references;
	C3DStream* _stream;
    std::vector<MeshSkinData*>* _meshSkins;
	bool _isSkin;
};
}

#endif
