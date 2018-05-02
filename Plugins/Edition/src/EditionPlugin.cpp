#include <EditionPlugin.hpp>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include <Engine/RadiumEngine.hpp>
#include <GuiBase/Utils/PickingManager.hpp>
#include <Engine/Renderer/Renderer.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Core/Math/LinearAlgebra.hpp>

#include <GuiBase/SelectionManager/SelectionManager.hpp>

#include <EditionSystem.hpp>

namespace EditionPlugin {

    EditionPluginC::~EditionPluginC() {}

	void EditionPluginC::registerPlugin(const Ra::PluginContext& context)
	{
		//Register a system here 
		EditionSystem* system = new EditionSystem;
		context.m_engine->registerSystem("EditionSystem", system);

        m_pickingManager = context.m_pickingManager;
        m_selectionManager = context.m_selectionManager;
	}

	bool EditionPluginC::doAddWidget(QString & name)
	{
		//initialize name and return true if you wish to add a widget in the toolbox
        name = "Edition";
        return true;
	}

	QWidget * EditionPluginC::getWidget()
	{
        QWidget* widget = new QWidget;
        QPushButton* resetButton = new QPushButton("Reset", widget);
        QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetSelectedEntity()));

        QVBoxLayout* layout = new QVBoxLayout(widget);

        layout->addWidget(resetButton);
        return widget;
	}

	bool EditionPluginC::doAddMenu()
	{
		//return true if you wish to add a menu
		return false;
	}

	QMenu * EditionPluginC::getMenu()
	{
		//create your menu here and return the pointer
		return nullptr;
	}

	bool EditionPluginC::doAddAction(int & nb)
	{
		nb = 0;
		return false;
	}

	QAction * EditionPluginC::getAction(int id)
	{
		return nullptr;
	}

    void EditionPluginC::resetSelectedEntity()
    {
        Ra::Engine::Renderer::PickingResult data = m_pickingManager->getCurrent();
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        std::cout << "selected picking :" << data.m_roIdx << std::endl;
        std::cout << "selected selection :" << item.m_roIndex << std::endl;

        /*if ( data.m_mode == Ra::Engine::Renderer::PickingMode::RO && Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->exists( data.m_roIdx ) )
        {
             std::shared_ptr<Ra::Engine::RenderObject> ro = Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject(data.m_roIdx);

             Ra::Core::Matrix4 transform;
             transform << 1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1;
             ro->setLocalTransform(transform);

             std::cout << "reset done" << std::endl;
        } else {
            std::cout << "cannot reset that" << std::endl;
        }*/
        if(item.isValid())
        {
            Ra::Core::Transform transform = Ra::Core::Transform::Identity();

            if (item.isEntityNode())
            {
                item.m_entity->setTransform(transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not an entity" << std::endl;
            }

            if (item.isComponentNode())
            {
                item.m_component->setTransform(item.m_roIndex, transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not a component" << std::endl;
            }

            if ( Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->exists( item.m_roIndex ) )
            {
                std::shared_ptr<Ra::Engine::RenderObject> ro = Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject(item.m_roIndex);
                ro->setLocalTransform(transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not a RO" << std::endl;
            }
        }
    }

}
