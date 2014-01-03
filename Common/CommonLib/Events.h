#pragma once

#include <functional>
#include <list>

namespace Utils {
	class EventScope;
	template <class T> class Event;

	class IEvent {
	public:
		virtual ~IEvent() {}
	public: // Attaching and Detaching events
		virtual void DetachForScope(EventScope &scope) = 0;
	};
	
	/// <summary>
	/// Used to define the scope within an event exists.
	/// Events are unhooked automatically on destruction.
	/// </summary>
	class EventScope final {
		std::list<std::reference_wrapper<IEvent>> m_HookedEvents;

	protected:
		template<class> friend class Event;
		void HookEvent(IEvent &event) { m_HookedEvents.push_front(std::ref(event)); }
		void DropEvent(IEvent &event) {
			auto i = m_HookedEvents.begin();
			while (i != m_HookedEvents.end()) {
				// Compare pointers
				if (&(*i).get() == &event) {
					// Remove Scope from List
					i = m_HookedEvents.erase(i);
				}
				else
					i++;
			}
		}

	public:
		~EventScope() {
			// Detach all Events from Scope
			for (IEvent &event : m_HookedEvents)
				event.DetachForScope(*this);
		}
	};

	/// <summary>
	/// Used for event hooking. Add to class as public member.
	/// </summary>
	template <class T> class Event : public IEvent{
	protected:
		typedef std::function<void(const T&)> Callback;

		// Internal Storage Entry
		struct CallbackEntry {
			Callback CallbackFunc;
			EventScope &Scope;
			CallbackEntry(Callback callback, EventScope &scope) :
				CallbackFunc(callback),
				Scope(scope)
			{}
			
			// Disallow Assign (TODO: Also disable copy and get that working)
			CallbackEntry& operator=(const CallbackEntry&) = delete;
		};

		std::list<CallbackEntry> m_Callbacks;

	public: // Attaching and Detaching Events
		void Attach(Callback callback, EventScope &scope) {
			// Register Function and Scope
			m_Callbacks.push_back(CallbackEntry(callback, scope));
			scope.HookEvent(*this);
		}

		template <typename ObjectType, typename MemberCallback>
		void AttachMember(ObjectType *object, MemberCallback callback, EventScope &scope) {
			Attach(std::bind(callback, object, std::placeholders::_1), scope);
		}

		/** Don't use this anymore, use AttachMember instead. */
		#define AttachFromThis(callback, scope) Attach(std::bind(&callback, this, std::placeholders::_1), scope)

		void DetachForScope(EventScope &scope) {
			auto i = m_Callbacks.begin();
			while (i != m_Callbacks.end()) {
				// Compare pointers
				if (&((*i).Scope) == &scope) {
					// Remove Scope from List
					i = m_Callbacks.erase(i);
				}
				else
					i++;
			}
		}

	public: // Event Invoking
		void Invoke(const T &param) {
			// Call all Functions in the Callbacks List
			for (CallbackEntry &entry : m_Callbacks)
				entry.CallbackFunc(param);
		}

	public: // Destructor
		virtual ~Event() {
			for (CallbackEntry &entry : m_Callbacks)
				entry.Scope.DropEvent(*this);
		}
	};

	struct EmptyEventArgs final {};
	const EmptyEventArgs NO_ARGS;

	class NoArgsEvent final : public Event<EmptyEventArgs> {
	public:
		void Invoke() {
			// Call all Functions in the Callbacks List
			for (CallbackEntry &entry : m_Callbacks)
				entry.CallbackFunc(NO_ARGS);
		}
	};
}