/*
 * Copyright (c) 2023, Kenneth Myhra <kennethmyhra@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/FormDataEventPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/HTML/FormDataEvent.h>

namespace Web::HTML {

GC_DEFINE_ALLOCATOR(FormDataEvent);

WebIDL::ExceptionOr<GC::Ref<FormDataEvent>> FormDataEvent::construct_impl(JS::Realm& realm, FlyString const& event_name, FormDataEventInit const& event_init)
{
    return realm.create<FormDataEvent>(realm, event_name, event_init);
}

FormDataEvent::FormDataEvent(JS::Realm& realm, FlyString const& event_name, FormDataEventInit const& event_init)
    : DOM::Event(realm, event_name, event_init)
    , m_form_data(event_init.form_data)
{
}

FormDataEvent::~FormDataEvent() = default;

void FormDataEvent::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(FormDataEvent);
    Base::initialize(realm);
}

void FormDataEvent::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_form_data);
}

}
