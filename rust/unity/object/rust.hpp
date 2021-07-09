#pragma once

#include "../sdk.hpp"

#include "system.hpp"
#include "unity_engine.hpp"

struct FacepunchBehaviour : UnityEngine::MonoBehaviour
{
	IL2CPP_CLASS( "FacepunchBehaviour" );
};

struct BaseMonoBehaviour : FacepunchBehaviour
{
	IL2CPP_CLASS( "BaseMonoBehaviour" );
};

struct Translate : Il2CppObject
{
	struct Phrase : Il2CppObject
	{
		IL2CPP_CLASS( "Translate.Phrase" );
		IL2CPP_FIELD( System::String*, token );
		IL2CPP_FIELD( System::String*, english );
	};
	IL2CPP_CLASS( "Translate" );
};

namespace Facepunch
{

IL2CPP_NAME_SPACE( "Facepunch" );

struct SkeletonDefinition : UnityEngine::ScriptableObject
{
	struct Bone
	{
		int Id = 0;																	// 0x0000
		int Depth = 0;															// 0x0004
		int Parent = 0;															// 0x0008
		FIELD_PAD( 0x0004 );												// 0x000C
		System::String* Name = nullptr;							// 0x0010
		UnityEngine::GameObject* Target = nullptr;	// 0x0018
		int Flags = 0;															// 0x0020
	};
	IL2CPP_CLASS( "SkeletonDefinition" );
	IL2CPP_FIELD( UnityEngine::GameObject*, SourceObject );
	IL2CPP_FIELD( System::Array< Bone >*, Bones );
};

struct Skeleton : UnityEngine::MonoBehaviour
{
	System::Array< SkeletonDefinition::Bone >* GetSourceBones()
	{
		const auto source = Source();

		if( memory::IsAddressValid( source ) )
		{
			return source->Bones();
		}

		return nullptr;
	}

	IL2CPP_CLASS( "Skeleton" );
	IL2CPP_FIELD( SkeletonDefinition*, Source );
	IL2CPP_FIELD( System::Array< UnityEngine::GameObject* >*, Bones );
};

} // namespace Facepunch

struct SkinnedMultiMesh : UnityEngine::MonoBehaviour
{
	System::Array< Facepunch::SkeletonDefinition::Bone >* GetSourceBones()
	{
		const auto player_skeleton = skeleton();

		if( memory::IsAddressValid( player_skeleton ) )
		{
			return player_skeleton->GetSourceBones();
		}

		return nullptr;
	}

	System::Array< UnityEngine::GameObject* >* GetBones()
	{
		const auto player_skeleton = skeleton();

		if( memory::IsAddressValid( player_skeleton ) )
		{
			return player_skeleton->Bones();
		}

		return nullptr;
	}

	IL2CPP_CLASS( "SkinnedMultiMesh" );
	IL2CPP_FIELD( Facepunch::Skeleton*, skeleton );
};

struct PlayerModel : FacepunchBehaviour
{
	System::Array< Facepunch::SkeletonDefinition::Bone >* GetSourceBones()
	{
		const auto player_mesh = _multiMesh();

		if( memory::IsAddressValid( player_mesh ) )
		{
			return player_mesh->GetSourceBones();
		}

		return nullptr;
	}

	System::Array< UnityEngine::GameObject* >* GetBones()
	{
		const auto player_mesh = _multiMesh();

		if( memory::IsAddressValid( player_mesh ) )
		{
			return player_mesh->GetBones();
		}

		return nullptr;
	}

	IL2CPP_CLASS( "PlayerModel" );
	IL2CPP_FIELD( SkinnedMultiMesh*, _multiMesh );
	IL2CPP_FIELD( bool, isLocalPlayer );
	IL2CPP_FIELD( UnityEngine::Vector3, velocity );
	IL2CPP_FIELD( UnityEngine::BoxCollider*, collision );
};

enum class ItemCategory : std::int32_t
{
	Weapon,
	Construction,
	Items,
	Resources,
	Attire,
	Tool,
	Medical,
	Food,
	Ammunition,
	Traps,
	Misc,
	All,
	Common,
	Component,
	Search,
	Favourite,
	Electrical,
	Fun,
};
// sizeof( ItemCategory ) = 0x0004

struct ItemDefinition : UnityEngine::MonoBehaviour
{
	IL2CPP_CLASS( "ItemDefinition" );
	IL2CPP_FIELD( std::int32_t, itemid );
	IL2CPP_FIELD( System::String*, shortname );
	IL2CPP_FIELD( ItemCategory, category );
};

struct Item : Il2CppObject
{
	IL2CPP_CLASS( "Item" );
	IL2CPP_FIELD( std::uint32_t, uid );
	IL2CPP_FIELD( ItemDefinition*, info );
};

struct ItemContainer : Il2CppObject
{
	IL2CPP_CLASS( "ItemContainer" );
	IL2CPP_FIELD( System::List< Item* >*, itemList );
};

struct PlayerInput : BaseMonoBehaviour
{
	void SetViewVars( const UnityEngine::Vector3& new_angles )
	{
		bodyAngles() = new_angles;
	}

	IL2CPP_CLASS( "PlayerInput" );
	IL2CPP_FIELD( Vector3, bodyAngles );
	IL2CPP_FIELD( Vector3, headAngles );
	IL2CPP_FIELD( Vector3, recoilAngles );
};

struct BaseNetworkable : BaseMonoBehaviour
{
	struct EntityRealm : Il2CppObject
	{
		using List = System::ListDictionary< std::uint32_t, BaseNetworkable* >;
		IL2CPP_FIELD( List*, entityList );
	};
	IL2CPP_CLASS( "BaseNetworkable" );
	IL2CPP_STATIC_FIELD( EntityRealm*, clientEntities );
	IL2CPP_FIELD( System::String*, _prefabName );
	IL2CPP_FIELD( System::String*, _prefabNameWithoutExtension );
	IL2CPP_PROPERTY( System::String*, PrefabName );
	IL2CPP_PROPERTY( System::String*, ShortPrefabName );
};

struct BaseEntity : BaseNetworkable
{
	IL2CPP_CLASS( "BaseEntity" );
	IL2CPP_FIELD( UnityEngine::Bounds, bounds );
	IL2CPP_FIELD( System::String*, _name );
};

struct ResourceEntity : BaseEntity
{
	IL2CPP_CLASS( "ResourceEntity" );
};

struct SkeletonProperties : UnityEngine::ScriptableObject
{
	struct BoneProperty : Il2CppObject
	{
		IL2CPP_CLASS( "SkeletonProperties.BoneProperty" );
		IL2CPP_FIELD( UnityEngine::GameObject*, bone );
		IL2CPP_FIELD( Translate::Phrase*, name );
		IL2CPP_FIELD( std::int32_t, area );
	};
	IL2CPP_CLASS( "SkeletonProperties" );
	IL2CPP_FIELD( UnityEngine::GameObject*, boneReference );
	IL2CPP_FIELD( System::Array< BoneProperty* >*, bones );
};

struct BaseCombatEntity : BaseEntity
{
	IL2CPP_CLASS( "BaseCombatEntity" );
	IL2CPP_FIELD( SkeletonProperties*, skeletonProperties );
	IL2CPP_PROPERTY( float, health );
};

struct PlayerInventory : Il2CppObject
{
	IL2CPP_CLASS( "PlayerInventory" );
	IL2CPP_FIELD( ItemContainer*, containerBelt );
};

__forceinline bool hooked_isAdmin_getter()
{
	return false;
}

struct BasePlayer : BaseCombatEntity
{
	typedef bool (*get_isAdmin)();

	bool IsLocalPlayer()
	{
		const auto player_model = playerModel();

		if( memory::IsAddressValid( player_model ) )
		{
			return player_model->isLocalPlayer();
		}

		return false;
	}

	std::size_t GetBoneCount()
	{
		const auto player_model = playerModel();

		if( memory::IsAddressValid( player_model ) )
		{
			const auto bone_array = player_model->GetBones();

			if( memory::IsAddressValid( bone_array ) )
			{
				return bone_array->max_length;
			}
		}

		return 0;
	}

	std::int32_t GetBoneParent( std::size_t index )
	{
		const auto player_model = playerModel();

		if( memory::IsAddressValid( player_model ) )
		{
			const auto player_bones = player_model->GetSourceBones();

			if( memory::IsAddressValid( player_bones ) )
			{
				const auto player_bone = player_bones->m_Items[ index ];
				return player_bone.Parent;
			}
		}

		return -1;
	}

	UnityEngine::Vector3 GetBone( std::size_t index )
	{
		const auto player_model = playerModel();

		if( memory::IsAddressValid( player_model ) )
		{
			const auto player_bones = player_model->GetBones();

			if( memory::IsAddressValid( player_bones ) )
			{
				const auto player_bone = player_bones->m_Items[ index ];

				if( memory::IsAddressValid( player_bone ) )
				{
					const auto transform = player_bone->get_transform();

					if( memory::IsAddressValid( transform ) )
					{
						return transform->get_position();
					}
				}
			}
		}

		return { };
	}

	UnityEngine::Vector3 GetVelocity()
	{
		const auto player_model = playerModel();

		if( memory::IsAddressValid( player_model ) )
		{
			return player_model->velocity();
		}

		return { };
	}

	Item* GetActiveItem()
	{
		const auto active_item = clActiveItem();
		const auto player_inventory = inventory();

		if( memory::IsAddressValid( player_inventory ) )
		{
			const auto belt = player_inventory->containerBelt();

			if( memory::IsAddressValid( belt ) )
			{
				const auto item_list = belt->itemList();

				if( memory::IsAddressValid( item_list ) )
				{
					const auto items = item_list->_items;

					if( memory::IsAddressValid( items ) )
					{
						for( std::int32_t index = 0; index < item_list->_size; index++ )
						{
							const auto item = items->m_Items[ index ];

							if( memory::IsAddressValid( item ) )
							{
								if( item->uid() == active_item )
								{
									return item;
								}
							}
						}
					}
				}
			}
		}

		return nullptr;
	}

	IL2CPP_CLASS( "BasePlayer" );
	IL2CPP_FIELD( PlayerModel*, playerModel );
	IL2CPP_FIELD( std::uint32_t, playerFlags );
	IL2CPP_FIELD( std::uint32_t, clActiveItem );
	IL2CPP_FIELD( PlayerInput*, input );
	IL2CPP_FIELD( PlayerInventory*, inventory );
	IL2CPP_FIELD(bool, wasDead);
	IL2CPP_FIELD(bool, wasSleeping);
	IL2CPP_PROPERTY( System::String*, displayName );

	bool m_isAdmin_getter_hooked = false;
	get_isAdmin m_restore_isAdmin_getter = nullptr;
	get_isAdmin m_current_isAdmin_getter = nullptr;
	int16_t m_restore_player_flags = 0;

	bool IsAdminGetterHooked()
	{
		return m_isAdmin_getter_hooked;
	}

	bool HookIsAdminGetter()
	{
		if (m_isAdmin_getter_hooked)
			return true;

		m_current_isAdmin_getter = reinterpret_cast<get_isAdmin>(win32::GetImage(HASH("GameAssembly.dll")) + 0x00307270);
		if (!memory::IsAddressValid(m_current_isAdmin_getter))
		{
			return false;
		}

		std::memcpy(m_restore_isAdmin_getter, m_current_isAdmin_getter, sizeof(uintptr_t));
		m_restore_player_flags = playerFlags();

		m_current_isAdmin_getter = &hooked_isAdmin_getter;
		m_isAdmin_getter_hooked = true;

		return true;
	}

	bool UnhookIsAdminGetter()
	{
		if (!m_isAdmin_getter_hooked)
			return true;

		if (!memory::IsAddressValid(m_restore_isAdmin_getter))
			return false;

		std::memcpy(m_current_isAdmin_getter, m_restore_isAdmin_getter, sizeof(uintptr_t));
		std::memset(m_restore_isAdmin_getter, 0, sizeof(uintptr_t));
		m_isAdmin_getter_hooked = false;

		return true;
	}
};

struct DecayEntity : BaseCombatEntity
{
	IL2CPP_CLASS( "DecayEntity" );
};

struct StabilityEntity : DecayEntity
{
	IL2CPP_CLASS( "StabilityEntity" );
};

struct BuildingBlock : StabilityEntity
{
	IL2CPP_CLASS( "BuildingBlock" );
};

struct BaseNpc : BaseCombatEntity
{
	IL2CPP_CLASS( "BaseNpc" );
};

struct BaseAnimalNPC : BaseNpc
{
	IL2CPP_CLASS( "BaseAnimalNPC" );
};

struct BaseTrap : DecayEntity
{
	IL2CPP_CLASS( "BaseTrap" );
};

struct BearTrap : BaseTrap
{
	IL2CPP_CLASS( "BearTrap" );
};

struct MapMarker : BaseEntity
{
	IL2CPP_CLASS( "MapMarker" );
};

struct VendingMachineMapMarker : MapMarker
{
	IL2CPP_CLASS( "VendingMachineMapMarker" );
};

struct StorageContainer : DecayEntity
{
	IL2CPP_CLASS( "StorageContainer" );
};

struct BoxStorage : StorageContainer
{
	IL2CPP_CLASS( "BoxStorage" );
};

struct StashContainer : StorageContainer
{
	IL2CPP_CLASS( "StashContainer" );
};

struct BuildingPrivlidge : StorageContainer
{
	IL2CPP_CLASS( "BuildingPrivlidge" );
};

struct Workbench : StorageContainer
{
	IL2CPP_CLASS( "Workbench" );
};

struct BaseOven : StorageContainer
{
	IL2CPP_CLASS( "BaseOven" );
};

struct ResearchTable : StorageContainer
{
	IL2CPP_CLASS( "ResearchTable" );
};

struct WorldItem : BaseEntity
{
	IL2CPP_CLASS( "WorldItem" );
};

struct DroppedItem : WorldItem
{
	IL2CPP_CLASS( "DroppedItem" );
};

struct BaseCorpse : BaseCombatEntity
{
	IL2CPP_CLASS( "BaseCorpse" );
};

struct LootableCorpse : BaseCorpse
{
	IL2CPP_CLASS( "LootableCorpse" );
};

struct PlayerCorpse : LootableCorpse
{
	IL2CPP_CLASS( "PlayerCorpse" );
};

struct GunTrap : StorageContainer
{
	IL2CPP_CLASS( "GunTrap" );
};

struct OreHotSpot : BaseCombatEntity
{
	IL2CPP_CLASS( "OreHotSpot" );
};