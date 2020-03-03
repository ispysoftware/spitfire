/*
 * Copyright (C) 2014 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_INTEGER_OPTIONAL_INTEGER_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_INTEGER_OPTIONAL_INTEGER_H_

#include "third_party/blink/renderer/core/svg/svg_integer.h"
#include "third_party/blink/renderer/core/svg/svg_parsing_error.h"
#include "third_party/blink/renderer/platform/heap/handle.h"

namespace blink {

class SVGIntegerOptionalInteger final : public SVGPropertyBase {
 public:
  // Tearoff of SVGIntegerOptionalInteger is never created.
  typedef void TearOffType;
  typedef void PrimitiveType;

  SVGIntegerOptionalInteger(SVGInteger* first_integer,
                            SVGInteger* second_integer);

  SVGIntegerOptionalInteger* Clone() const;
  SVGPropertyBase* CloneForAnimation(const String&) const override;

  String ValueAsString() const override;
  SVGParsingError SetValueAsString(const String&);
  void SetInitial(unsigned);
  static constexpr int kInitialValueBits = SVGInteger::kInitialValueBits;

  void Add(SVGPropertyBase*, SVGElement*) override;
  void CalculateAnimatedValue(const SVGAnimateElement&,
                              float percentage,
                              unsigned repeat_count,
                              SVGPropertyBase* from,
                              SVGPropertyBase* to,
                              SVGPropertyBase* to_at_end_of_duration_value,
                              SVGElement* context_element) override;
  float CalculateDistance(SVGPropertyBase* to,
                          SVGElement* context_element) override;

  static AnimatedPropertyType ClassType() {
    return kAnimatedIntegerOptionalInteger;
  }
  AnimatedPropertyType GetType() const override { return ClassType(); }

  SVGInteger* FirstInteger() const { return first_integer_; }
  SVGInteger* SecondInteger() const { return second_integer_; }

  void Trace(blink::Visitor*) override;

 protected:
  Member<SVGInteger> first_integer_;
  Member<SVGInteger> second_integer_;
};

DEFINE_SVG_PROPERTY_TYPE_CASTS(SVGIntegerOptionalInteger);

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_INTEGER_OPTIONAL_INTEGER_H_
